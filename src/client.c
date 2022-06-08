#include "common.h"
#include "file_io.h"
#include "rdt.h"

void download_file(int sock) {
    rdt_seq_t seq;
    rdt_ack_t ack;
    ssize_t bytes_read;
    struct sockaddr_in server_addr;
    uint32_t data_len;
    char msg[512];
    char buf[512];
    int fd;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_addr.sin_port = htons(5000);

    struct sockaddr_in peer_addr;
    socklen_t peer_len = sizeof(peer_addr);

    sprintf(msg, "data/message.txt");
    seq.len = sizeof(seq) + strlen("data/message.txt");

    sendto(sock, &seq, sizeof(seq), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    sendto(sock, msg, seq.len - sizeof(seq), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    memset(msg, 0, sizeof(msg));

    fd = file_open((char *)"/tmp/download.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);

    while (1) {
        bytes_read = recvfrom(sock, &seq, sizeof(seq), 0, (struct sockaddr *)&peer_addr, &peer_len);
        if (bytes_read == 0) {
            printf("Peer closed connection\n");
            break;
        }
        assert(bytes_read == sizeof(seq));

        data_len = seq.len - sizeof(seq);
        bytes_read = recvfrom(sock, buf, data_len, 0, (struct sockaddr *)&peer_addr, &peer_len);
        assert(bytes_read == data_len);

        file_write_chunk(fd, buf, data_len);

        ack.len = sizeof(ack);
        ack.ackno = seq.seqno + 1;
        sendto(sock, &ack, sizeof(ack), 0, (struct sockaddr *)&peer_addr, peer_len);
    }

    printf("Download complete\n");
    close(sock);
}

int main(void) {
    int sock = create_udp_socket(0);
    download_file(sock);
}
