#include "s21_string.h"

void *s21_strchr(const char *str, int c) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  unsigned char *tmpstr1 = (unsigned char *)str;

  for (; *tmpstr1 != '\0'; tmpstr1++) {
    if (*tmpstr1 == c) {
      return tmpstr1;
    }
  }
  if (c == '\0') {
    return tmpstr1;
  }

  return S21_NULL;
}
