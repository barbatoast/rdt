#include "common.h"
#include "file_io.h"
#include "rdt.h"

void server_loop(int sock) {
    rdt_seq_t seq;
    rdt_ack_t ack;
    ssize_t bytes_read;
    struct sockaddr_in client_addr;
    uint32_t data_len;
    char msg[512];
    int handler;
    socklen_t client_len = sizeof(client_addr);
    int fd;
    int res;
    int seqno = 0;

    while (1) {
        bytes_read = recvfrom(sock, &seq, sizeof(seq), 0, (struct sockaddr *)&client_addr, &client_len);
        assert(bytes_read == sizeof(seq));

        data_len = seq.len - sizeof(seq);
        memset(msg, 0, sizeof(msg));
        bytes_read = recvfrom(sock, msg, data_len, 0, (struct sockaddr *)&client_addr, &client_len);
        assert(bytes_read == data_len);

        msg[data_len] = '\0';
        printf("Client requesting to download file: %s\n", msg);
        fd = file_open(msg, O_RDONLY, 0666);
        handler = create_udp_socket(0);

        while (1) {
            res = file_read_chunk(fd, msg, 500);
            if (res == 0) {
                break;
            }

            seq.len = sizeof(seq) + res;
            seq.seqno = seqno;

            sendto(handler, &seq, sizeof(seq), 0, (struct sockaddr *)&client_addr, client_len);
            sendto(handler, msg, seq.len - sizeof(seq), 0, (struct sockaddr *)&client_addr, client_len);

            bytes_read = recvfrom(handler, &ack, sizeof(ack), 0, (struct sockaddr *)&client_addr, &client_len);
            assert(bytes_read = sizeof(ack));
            assert(seq.seqno + 1 == ack.ackno);

            seqno++;
        }

        sendto(handler, NULL, 0, 0, (struct sockaddr *)&client_addr, client_len);
        close(handler);
        file_close(fd);
    }
}

int main(void) {
    int sock = create_udp_socket(5000);
    server_loop(sock);
}
