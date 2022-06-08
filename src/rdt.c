#include "rdt.h"

int create_udp_socket(int port) {
    int sock;
    int optval = 1;
    struct sockaddr_in addr;
    int err;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock >= 0);

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval));

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    //addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_addr.s_addr = htonl(0);
    addr.sin_port = htons(port);

    err = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    assert(err >= 0);

    return sock;
}
