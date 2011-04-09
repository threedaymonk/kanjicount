#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define UNICODE_MAX 0x10FFFF

uint32_t read_utf8_codepoint(FILE* fp){
  uint32_t result;
  uint8_t byte;
  int i, j, k;

  byte = fgetc(fp);

  if (byte < 0x80 || byte == 0xFF) return byte;

  for (i = 0, j = 5; i < 5; i++, j--) {
    if ((byte & (0x7F << j)) == (0xFF & (0x7E << j))) {
      result = (byte & (0x1F >> i)) << ((i + 1) * 6);
      for (k = i; k >= 0; k--) {
        byte = fgetc(fp);
        if (byte >> 6 != 2) return 0;
        result += (byte & 0x3F) << (k * 6);
      }
      return result;
    }
  }
  return 0;
}

int main(int argc, char** argv) {
  uint64_t* table;
  uint32_t codepoint;

  table = (uint64_t *)malloc(sizeof(uint64_t) * (UNICODE_MAX + 1));
  if (table == NULL) {
    fprintf(stderr, "Unable to allocate memory.");
    return 1;
  }
  memset(table, 0, sizeof(uint64_t) * (UNICODE_MAX+ 1));

  while (!feof(stdin)) {
    codepoint = read_utf8_codepoint(stdin);
    if (codepoint != 0x00 && codepoint != 0xFF) {
      table[codepoint] += 1;
    }
  }

  for (codepoint = 0; codepoint <= UNICODE_MAX; codepoint++) {
    if (table[codepoint] > 0) {
      printf("%X, %" PRId64 "\n", codepoint, table[codepoint]);
    }
  }

  return 0;
}