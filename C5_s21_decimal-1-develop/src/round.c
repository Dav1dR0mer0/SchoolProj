#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error_code = 0;

  s21_big_decimal tmp_result = dec_to_big_dec(value);

  if (tmp_result.scale > 28) {
    error_code = 1;
  } else {
    unsigned int first_frac_int = 0;
    while (tmp_result.scale > 0) {
      first_frac_int = big_dec_div_remn_by_10(&tmp_result);

      tmp_result.scale--;
    }

    if (first_frac_int > 5u) {
      tmp_result.bits[0] += 1u;
      get_and_set_ovf(&tmp_result);
    }

    *result = big_dec_to_dec(tmp_result);
  }

  return error_code;
}
