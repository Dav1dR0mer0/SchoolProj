#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  const char *ptr = str;
  if (ptr == S21_NULL) return 0;
  const char *p_s = ptr;
  while (*p_s) p_s++;
  return p_s - ptr;
}