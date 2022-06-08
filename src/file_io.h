#ifndef RDT_FILE_IO_H
#define RDT_FILE_IO_H

#include "common.h"

int file_open(char *filename, int flags, int mode);

int file_read_chunk(int fd, char *buf, size_t len);

void file_write_chunk(int fd, char *buf, size_t len);

void file_close(int fd);

void file_swap(void);

#endif  // RDT_FILE_IO_H
