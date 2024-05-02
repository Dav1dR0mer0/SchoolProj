#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *destination = (unsigned char *)dest;
  const unsigned char *source = (const unsigned char *)src;
  for (s21_size_t j = 0; j < n; j++) {
    destination[j] = source[j];
  }
  return dest;
}
