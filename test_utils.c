#include "utils.h"

int main(){
  // on crée un petit fichier dans lequel on va écrire 4 octets :  0xAA, 0xBB, 0xCC, 0xDD (dans cet ordre, le fichier va donc contenir 0xAABBCCDD)
  // ensuite on va le lire en big indian, normalement on devrait lire 0xAABBCCDD puis en little indian, on devrait lire alors 0xDDCCBBAA

  FILE* f = fopen("file.bin", "w");
  uint8_t a[4] = {0xAA, 0xBB, 0xCC, 0xDD};
  fwrite(a, sizeof(uint8_t), 4, f); // on écrit ce qu'on veut dans le code 
  fclose(f);

  f = fopen("file.bin", "r");
  // on lit en big indian
  uint32_t i = read_uint32_bigendian(f);
  printf("Big Indian : %x\n", i);

  // on lit en little indian après être retourné au début du fichier
  fseek(f, 0L, SEEK_SET);
  
  i = read_uint32_littleendian(f);
  printf("Little Indian : %x\n", i);
  
  return 0;
}
