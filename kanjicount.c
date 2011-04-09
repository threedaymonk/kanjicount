#include <stdio.h>
#include <stdint.h>

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
  while (!feof(stdin)) {
    printf("U+%04X\n", read_utf8_codepoint(stdin));
  }
  return 0;
}
