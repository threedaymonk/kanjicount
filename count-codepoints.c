// Count the number of occurrences of each Unicode codepoint read on stdin
// Print a report with lines of the form:
//     <codepoint in hex>,<number of occurrences>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define UNICODE_RANGE 0x110000

uint32_t read_utf8_codepoint(FILE* fp){
  uint32_t result, byte, i, j, k;

  byte = (uint32_t)fgetc(fp);

  if (byte < 0x80 || byte == 0xFF) return byte;

  for (i = 0, j = 5; i < 5; i++, j--) {
    if ((byte & (0x7F << j)) == ((uint32_t)0xFF & (0x7E << j))) {
      result = ((byte & (0x1F >> i)) << ((i + 1) * 6));
      for (k = 0; k <= i; k++) {
        byte = (uint32_t)fgetc(fp);
        if (byte >> 6 != 2) return 0;
        result += (byte & 0x3F) << ((i - k) * 6);
      }
      return result;
    }
  }
  return 0;
}

int main(int argc, char** argv){
  uint64_t* table;
  uint32_t codepoint;

  table = (uint64_t*)malloc(sizeof(uint64_t) * UNICODE_RANGE);
  if (table == NULL) {
    fprintf(stderr, "Unable to allocate memory.");
    return 1;
  }
  memset(table, 0, sizeof(uint64_t) * UNICODE_RANGE);

  while (0 == feof(stdin)) {
    codepoint = read_utf8_codepoint(stdin);
    if (codepoint != 0x00 && codepoint != 0xFF && codepoint < UNICODE_RANGE) {
      table[codepoint] += 1;
    }
  }

  for (codepoint = 0; codepoint < UNICODE_RANGE; codepoint++) {
    if (table[codepoint] > 0) {
      printf("%jX, %ju\n", (uintmax_t)codepoint, (uintmax_t)table[codepoint]);
    }
  }

  free(table);

  return 0;
}
