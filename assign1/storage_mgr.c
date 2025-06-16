#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "storage_mgr.h"
#include "dberror.h"

void initStorageManager(void) {
}

RC createPageFile(char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (!file)
        return RC_FILE_NOT_FOUND;

    char *page = (char *)calloc(PAGE_SIZE, sizeof(char));
    if (!page) {
        fclose(file);
        return RC_MEMORY_ALLOCATION_FAILED;
    }

    fwrite(page, sizeof(char), PAGE_SIZE, file);
    free(page);

    int totalNumPages = 1;
    fseek(file, 0, SEEK_SET);
    fwrite(&totalNumPages, sizeof(int), 1, file);
    fclose(file);
    return RC_OK;
}

RC openPageFile(char *fileName, SM_FileHandle *fHandle) {
    FILE *file = fopen(fileName, "r+");
    if (!file)
        return RC_FILE_NOT_FOUND;

    int totalNumPages;
    fread(&totalNumPages, sizeof(int), 1, file);

    fHandle->fileName = strdup(fileName);
    fHandle->totalNumPages = totalNumPages;
    fHandle->curPagePos = 0;
    fHandle->mgntInfo = file;
    return RC_OK;
}

RC closePageFile(SM_FileHandle *fHandle) {
    if (fHandle->mgntInfo) {
        fclose((FILE *)fHandle->mgntInfo);
        fHandle->mgntInfo = NULL;
    }
    if (fHandle->fileName) {
        free(fHandle->fileName);
        fHandle->fileName = NULL;
    }
    return RC_OK;
}

RC destroyPageFile(char *fileName) {
    if (unlink(fileName) != 0)
        return RC_FILE_NOT_FOUND;
    return RC_OK;
}

RC readBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {
    if (pageNum < 0 || pageNum >= fHandle->totalNumPages)
        return RC_READ_NON_EXISTING_PAGE;

    FILE *file = (FILE *)fHandle->mgntInfo;
    fseek(file, sizeof(int) + pageNum * PAGE_SIZE, SEEK_SET);
    size_t bytesRead = fread(memPage, sizeof(char), PAGE_SIZE, file);
    if (bytesRead != PAGE_SIZE)
        return RC_READ_NON_EXISTING_PAGE;

    fHandle->curPagePos = pageNum;
    return RC_OK;
}

RC getBlockPos(SM_FileHandle *fHandle) {
    return fHandle->curPagePos;
}

RC readFirstBlock(SM_FileHandle *fHandle, SM_PageHandle memPage) {
    return readBlock(0, fHandle, memPage);
}

RC readPreviousBlock(SM_FileHandle *fHandle, SM_PageHandle memPage) {
    return readBlock(fHandle->curPagePos - 1, fHandle, memPage);
}

RC readCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage) {
    return readBlock(fHandle->curPagePos, fHandle, memPage);
}

RC readNextBlock(SM_FileHandle *fHandle, SM_PageHandle memPage) {
    return readBlock(fHandle->curPagePos + 1, fHandle, memPage);
}

RC readLastBlock(SM_FileHandle *fHandle, SM_PageHandle memPage) {
    return readBlock(fHandle->totalNumPages - 1, fHandle, memPage);
}

RC writeBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {
    if (pageNum < 0 || pageNum >= fHandle->totalNumPages)
        return RC_WRITE_FAILED;

    FILE *file = (FILE *)fHandle->mgntInfo;
    fseek(file, sizeof(int) + pageNum * PAGE_SIZE, SEEK_SET);
    fwrite(memPage, sizeof(char), PAGE_SIZE, file);
    fHandle->curPagePos = pageNum;
    return RC_OK;
}

RC writeCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage) {
    return writeBlock(fHandle->curPagePos, fHandle, memPage);
}

RC appendEmptyBlock(SM_FileHandle *fHandle) {
    FILE *file = (FILE *)fHandle->mgntInfo;
    char *page = (char *)calloc(PAGE_SIZE, sizeof(char));
    if (!page)
        return RC_MEMORY_ALLOCATION_FAILED;

    fseek(file, 0, SEEK_END);
    fwrite(page, sizeof(char), PAGE_SIZE, file);
    free(page);

    fHandle->totalNumPages++;
    fseek(file, 0, SEEK_SET);
    fwrite(&fHandle->totalNumPages, sizeof(int), 1, file);
    return RC_OK;
}

RC ensureCapacity(int numberOfPages, SM_FileHandle *fHandle) {
    while (fHandle->totalNumPages < numberOfPages) {
        RC rc = appendEmptyBlock(fHandle);
        if (rc != RC_OK)
            return rc;
    }
    return RC_OK;
}
