#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  void *insert = S21_NULL;
  if (src == S21_NULL || str == S21_NULL) {
    return S21_NULL;
  }

  int i = 0, j = 0;
  int src_length = 0;
  int str_length = 0;
  while (src[src_length] != '\0') {
    src_length++;
  }
  while (str[str_length] != '\0') {
    str_length++;
  }

  if (start_index > (long unsigned int)src_length) {
    return S21_NULL;
  }

  insert = malloc((str_length + src_length + 1) * sizeof(char));
  if (insert != S21_NULL) {
    for (; (unsigned long)i < start_index; i++) {
      ((char *)insert)[i] = src[i];
    }
    for (; j < str_length; j++, i++) {
      ((char *)insert)[i] = str[j];
    }
    for (j = start_index; j < src_length; j++, i++) {
      ((char *)insert)[i] = src[j];
    }
    ((char *)insert)[i] = '\0';
  }
  return insert;
}
