#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (src == S21_NULL) {
    dest = S21_NULL;
  } else {
    s21_size_t j = 0;
    for (; j < n && src[j] != '\0'; j++) {
      dest[j] = src[j];
    }
    for (; j < n; j++) {
      dest[j] = '\0';
    }
  }
  return dest;
}