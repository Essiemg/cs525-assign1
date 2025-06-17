#ifndef DBERROR_H
#define DBERROR_H

typedef int RC;

#define RC_OK 0
#define RC_FILE_NOT_FOUND 1
#define RC_READ_NON_EXISTING_PAGE 2
#define RC_MEMORY_ALLOCATION_FAILED 5
#define RC_WRITE_FAILED 6

extern void printError(RC error);

#endif
