#include "s21_string.h"

// margarme

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;
  void *result = S21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (s[i] == (unsigned char)c) {
      result = (void *)(s + i);
      i = n;
    }
  }
  return result;
}
