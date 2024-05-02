#include "s21_string.h"

void* s21_memset(void* ptr, int value, s21_size_t n) {
  unsigned char* ptsr = (unsigned char*)ptr;
  unsigned char aa = (unsigned char)value;
  for (s21_size_t j = 0; j < n; j++) {
    ptsr[j] = aa;
  }
  return ptr;
}
