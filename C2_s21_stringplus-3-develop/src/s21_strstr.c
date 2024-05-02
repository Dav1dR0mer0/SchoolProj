#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  unsigned char *tmpstr1 = (unsigned char *)haystack;
  unsigned char *tmpstr2 = (unsigned char *)needle;

  if (*tmpstr2 == '\0') {
    return (char *)haystack;
  }

  for (; *tmpstr1 != '\0'; tmpstr1++) {
    const unsigned char *ptr1 = tmpstr1;
    const unsigned char *ptr2 = tmpstr2;

    while (*ptr1 != '\0' && *ptr2 != '\0' && *ptr1 == *ptr2) {
      ptr1++;
      ptr2++;
    }

    if (*ptr2 == '\0') {
      return (char *)tmpstr1;
    }
  }

  return S21_NULL;
}
