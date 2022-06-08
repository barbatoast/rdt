#include "utest.h"

#include "file_io.h"

UTEST(file_io, swap) {
    file_swap();
    ASSERT_EQ(NULL, NULL);
}

UTEST_MAIN();
