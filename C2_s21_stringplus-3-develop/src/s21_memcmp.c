#include "s21_string.h"

int s21_memcmp(const void *s1, const void *s2, s21_size_t n) {
  const unsigned char *p1 = s1, *p2 = s2;
  while (n--) {
    if (*p1 != *p2) {
      return *p1 - *p2;
    } else {
      p1++;
      p2++;
    }
  }
  return 0;
}