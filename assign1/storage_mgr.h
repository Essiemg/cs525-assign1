#ifndef STORAGE_MGR_H
#define STORAGE_MGR_H

#include "dberror.h"

#define PAGE_SIZE 4096

typedef struct SM_FileHandle {
    char *fileName;
    int totalNumPages;
    int curPagePos;
    void *mgntInfo;
} SM_FileHandle;

typedef char *SM_PageHandle;

extern void initStorageManager(void);
extern RC createPageFile(char *fileName);
extern RC openPageFile(char *fileName, SM_FileHandle *fHandle);
extern RC closePageFile(SM_FileHandle *fHandle);
extern RC destroyPageFile(char *fileName);
extern RC readBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC getBlockPos(SM_FileHandle *fHandle);
extern RC readFirstBlock(SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC readPreviousBlock(SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC readCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC readNextBlock(SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC readLastBlock(SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC writeBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC writeCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage);
extern RC appendEmptyBlock(SM_FileHandle *fHandle);
extern RC ensureCapacity(int numberOfPages, SM_FileHandle *fHandle);

#endif
