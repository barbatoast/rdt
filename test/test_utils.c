#include "utest.h"

#include "utils.h"

UTEST(utils, calculate_checksum) {
    char *msg = "The quick brown fox jumps over the lazy dog";
    uint32_t checksum = calculate_checksum(msg, strlen(msg));
    ASSERT_EQ(checksum, 0x414fa339);
}

UTEST_MAIN();
