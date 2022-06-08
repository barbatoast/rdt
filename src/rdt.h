#ifndef RDT_RDT_H
#define RDT_RDT_H

#include "common.h"

typedef struct {
    uint16_t cksum;
    uint16_t len;
    uint32_t seqno;
} __attribute__ ((packed)) rdt_seq_t;

typedef struct {
    uint16_t cksum;
    uint16_t len;
    uint32_t ackno;
} __attribute__ ((packed)) rdt_ack_t;

int create_udp_socket(int port);

#endif  // RDT_RDT_H
