Storage Manager Implementation - CS 525 Assignment 1

### Solution Overview
Implements a storage manager for page files, supporting file operations and page read/write with absolute/relative addressing. Metadata (total pages) is stored at the file's start.

### Code Structure
- **storage_mgr.c**: Core implementation.
- **dberror.c**/**dberror.h**: Error handling.
- **storage_mgr.h**: Interface.
- **test_assign1_1.c**/**test_helper.h**: Tests.
- **Makefile**: Builds `test_assign1`.
- **README.txt**: This file.

### Implementation Notes
- Stores `totalNumPages` in first 4 bytes.
- Uses `FILE *` in `mgntInfo`.
- Handles errors via `RC` codes.
- Allocates memory dynamically.

### Usage
1. Run `make` to compile.
2. Run `./test_assign1` to test.
3. Use `gdb` or `valgrind` for debugging.

### Debugging
Checks for invalid pages and memory issues. Use `valgrind` for memory leaks.
