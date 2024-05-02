#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error_code = 0;

  s21_big_decimal tmp_result = dec_to_big_dec(value);

  if (tmp_result.scale > 28) {
    error_code = 1;
  } else {
    if (value.bits[3] & MINUS) {
      s21_big_decimal value_horse = dec_to_big_dec(value);

      s21_big_decimal zero = {0};

      s21_truncate(value, &value);

      s21_big_decimal tmp_value = dec_to_big_dec(value);

      s21_big_decimal fractional = dec_sub(&value_horse, &tmp_value);

      if (greater_not(&fractional, &zero)) {
        tmp_value.bits[0] += 1u;
        get_and_set_ovf(&tmp_value);
      }

      *result = big_dec_to_dec(tmp_value);
    } else {
      s21_truncate(value, result);
    }
  }

  return error_code;
}
