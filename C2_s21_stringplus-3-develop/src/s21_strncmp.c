#include <string.h>

#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int flag = 0;
  if (str1 != S21_NULL && str2 != S21_NULL) {
    while (n && (*str1 || *str2) && (*str1 == *str2)) {
      n--;
      str1++;
      str2++;
    }
    if (n != 0) {
      flag = *(unsigned char *)str1 - *(unsigned char *)str2;
    }
  } else if (str1 == S21_NULL || str2 == S21_NULL) {
    flag = 1;
  }
  return flag;
}
