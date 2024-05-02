#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  const unsigned char *tmpstr1 = (unsigned char *)str1;

  for (; *tmpstr1 != '\0'; tmpstr1++) {
    for (const unsigned char *tmpstr2 = (unsigned char *)str2; *tmpstr2 != '\0';
         tmpstr2++) {
      if (*tmpstr1 == *tmpstr2) {
        return (char *)tmpstr1;
      }
    }
  }

  return S21_NULL;
}