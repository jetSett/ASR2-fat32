#include <stdio.h>
#include <stdint.h>

uint8_t read_uint8(FILE *fd);

uint16_t read_uint16_littleendian(FILE *fd);
uint32_t read_uint32_littleendian(FILE *fd);

uint16_t read_uint16_bigendian(FILE *fd);
uint32_t read_uint32_bigendian(FILE *fd);

char* utf16_to_utf8(const char *str, size_t size);
