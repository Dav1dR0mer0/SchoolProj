#include "s21_string.h"

char* s21_strcpy(char* destination, const char* source) {
  char* ptr = destination;

  while (*source != '\0') {
    *ptr++ = *source++;
  }

  *ptr = '\0';

  return destination;
}