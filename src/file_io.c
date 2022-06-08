#include "file_io.h"

int file_open(char *filename, int flags, int mode) {
    int fd;

    fd = open(filename, flags, mode);
    assert(fd != -1);

    return fd;
}

int file_read_chunk(int fd, char *buf, size_t len) {
    ssize_t bytes_read;

    bytes_read = read(fd, buf, len);
    assert(bytes_read >= 0);

    return bytes_read;
}

void file_write_chunk(int fd, char *buf, size_t len) {
    write(fd, buf, len);
}

void file_close(int fd) {
    close(fd);
}

void file_swap(void) {
    int fd1, fd2;
    char buf[500];
    ssize_t bytes_read;

    fd1 = open("data/message.txt", O_RDONLY);
    assert(fd1 != -1);

    fd2 = open("/tmp/download.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    assert(fd2 != -1);

    do {
        bytes_read = read(fd1, buf, sizeof(buf));
        assert(bytes_read >= 0);
        write(fd2, buf, bytes_read);
    } while(bytes_read > 0);

    close(fd1);
    close(fd2);
}
