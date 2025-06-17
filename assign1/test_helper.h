#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <stdio.h>

#define ASSERT_TRUE(x, msg) if (!(x)) { printf("Test failed: %s\n", msg); exit(1); }

#endif
