#include <stdlib.h>
#include <string.h>
#include "storage_mgr.h"
#include "dberror.h"
#include "test_helper.h"

// Existing tests (from instructor-provided file, if any)
// Add your new test here
void testInvalidPageRead() {
    SM_FileHandle fHandle;
    char *memPage = (char *)malloc(PAGE_SIZE);
    ASSERT_TRUE(createPageFile("testfile.bin") == RC_OK, "Create file failed");
    ASSERT_TRUE(openPageFile("testfile.bin", &fHandle) == RC_OK, "Open file failed");
    ASSERT_TRUE(readBlock(10, &fHandle, memPage) == RC_READ_NON_EXISTING_PAGE, "Reading non-existent page should fail");
    closePageFile(&fHandle);
    destroyPageFile("testfile.bin");
    free(memPage);
}

int main() {
    // Call existing tests (if any)
    testInvalidPageRead();
    return 0;
}
