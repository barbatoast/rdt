#include "utils.h"

/**
 * @brief calculate the CRC-32 checksum
 * 
 * @param buf 
 * @param len 
 * @return uint32_t
 */
uint32_t calculate_checksum(uint8_t *buf, size_t len)
{
    size_t i, j;
    uint32_t byte, crc, mask;

    crc = 0xffffffff;
    for (i = 0; i < len; i++) {
        byte = buf[i];
        crc = crc ^ byte;
        for (j = 0; j < 8; j++) {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xedb88320 & mask);
        }
    }

    return ~crc;
}
