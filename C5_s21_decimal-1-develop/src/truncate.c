#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error_code = 0;

  s21_big_decimal tmp_result = dec_to_big_dec(value);

  if (tmp_result.scale > 28) {
    error_code = 1;
  } else {
    while (tmp_result.scale != 0) {
      big_dec_div_remn_by_10(&tmp_result);

      tmp_result.scale--;
    }
    *result = big_dec_to_dec(tmp_result);
  }

  return error_code;
}