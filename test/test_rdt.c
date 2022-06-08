#include "utest.h"

#include "rdt.h"

UTEST(rdt, packets) {
    ASSERT_EQ(sizeof(rdt_seq_t), 8);
    ASSERT_EQ(sizeof(rdt_ack_t), 8);
}

UTEST_MAIN();
