#include <iconv.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

uint8_t read_uint8(FILE *fd) {
  uint8_t out = 0;
  fread(&out, sizeof(uint8_t), 1, fd);
  return out;
}

uint16_t read_uint16_littleendian(FILE *fd) {
  uint8_t t[2];
  fread(t, sizeof(uint8_t), 2, fd);
  return (uint16_t)(t[0] + (t[1]<<8));
}
uint32_t read_uint32_littleendian(FILE *fd) {
  uint8_t t[4];
  fread(t, sizeof(uint8_t), 4, fd);
  return (uint32_t)(t[0] + (t[1]<<8) + (t[2]<<16) + (t[3]<<24));
}

uint16_t read_uint16_bigendian(FILE *fd) {
  uint8_t t[2];
  fread(t, sizeof(uint8_t), 2, fd);
  return (uint16_t)(t[1] + (t[0]<<8));
}
uint32_t read_uint32_bigendian(FILE *fd) {
  uint8_t t[4];
  fread(t, sizeof(uint8_t), 4, fd);
  return (uint32_t)(t[3] + (t[2]<<8) + (t[1]<<16) + (t[0]<<24));
}

char* utf16_to_utf8(const char *str, size_t size) {
  /* On alloue un buffer deux fois plus gros que l'entrée. Dans la
   * plupart des cas c'est trop ; mais c'est le moyen le plus simple
   * de s'assurer qu'on ne fait pas de dépassement de buffer
   * dans cette situation. */
  char *outbuf = malloc(size*2);
  assert(outbuf);

  /* FIXME: useless copy, because iconv takes a char** as inbuf instead
   * of const char**. */
  char *inbuf = malloc(size);
  assert(inbuf);
  memcpy(inbuf, str, size);

  size_t inbytesleft=size, outbytesleft=size*2;
  iconv_t conv = iconv_open("UTF-8", "UTF-16LE");

  char *inbuf_it = inbuf;
  char *outbuf_it = outbuf;
  while (inbytesleft > 0) {
    size_t res = iconv(conv, &inbuf_it, &inbytesleft, &outbuf_it, &outbytesleft);
    if (res == (size_t) -1) {
      perror("Error converting from UTF16 to UTF8");
      exit(EXIT_FAILURE);
    }
  }
  iconv_close(conv);
  free(inbuf);
  return outbuf;
}
