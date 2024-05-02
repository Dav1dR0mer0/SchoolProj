#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error_code = 0;

  *result = value;
  result->bits[3] = result->bits[3] ^ MINUS;

  return error_code;
}
