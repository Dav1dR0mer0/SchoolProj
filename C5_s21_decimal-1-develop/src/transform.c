#include "s21_decimal.h"

// Преобразователь	Функция
// Из int
// Из float	int s21_from_float_to_decimal(float src, s21_decimal *dst)
// В int
// В float	int s21_from_decimal_to_float(s21_decimal src, float *dst)

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error_code = 0;
  set_bits_zero(dst, 1);
  dst->bits[3] = ((dst->bits[3] | (src >> 31)) << 31);  // TODO это переписать
  if (src > 0) {
    dst->bits[0] = src;
  } else if (src < 0) {
    dst->bits[0] = change_int_to_direct_code(src);
  } else {
    error_code = 1;
  }

  return error_code;
}

int change_int_to_direct_code(int dst) {
  dst = (~dst) + 1;
  return dst;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error_code;
  int scale = get_raw_scale(&src);

  s21_big_decimal src_big = dec_to_big_dec(src);

  while (scale > 0) {
    big_dec_div_remn_by_10(&src_big);
    scale--;
  }
  src = big_dec_to_dec(src_big);

  if (src.bits[1] | src.bits[2] | (src.bits[0] & 0x80000000)) {
    error_code = 1;
  } else {
    *dst = src.bits[0];
    if (get_sign(&src)) {
      *dst = -(*dst);
    }
  }

  return error_code;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error_code = 0;
  set_bits_zero(dst, 1);
  s21_big_decimal tmp_result = dec_to_big_dec(*dst);

  // s21_big_decimal tmp = dec_to_big_dec(*dst);

  if (isinf(src) || isnan(src) || (src != src)) {
    error_code = 1;
  } else if (src != 0) {
    if (src < 0)  // с float нормально побитово не поработаешь, а в int кидать//
                  // слишком долго
    {
      src = -src;
      tmp_result.sign = 1u;
    }
    f_to_dec_set_mant_sign_and_scale(&src, &tmp_result);
  }
  *dst = big_dec_to_dec(tmp_result);

  return error_code;
}

void f_to_dec_set_mant_sign_and_scale(float *src, s21_big_decimal *tmp_result) {
  // m . m m m m m m E s e  e
  // 0 1 2 3 4 5 6 7 8 9 10 11
  char formated_float[15];
  sprintf(formated_float, "%.6E", *src);

  int i = 0;
  int pre_exp = -6;
  int exp = 0;
  int exp_sign = 1;

  while (i < 8) {
    if (i != 1) {
      tmp_result->bits[0] *= 10;
      tmp_result->bits[0] += (formated_float[i] - 48);
    }
    i++;
  }  // i == 8
  i = 9;

  if (formated_float[i] == '-') {
    exp_sign = -1;
  }
  i++;  // i == 10

  while (i < 12) {
    exp *= 10;
    exp += (formated_float[i] - 48);

    i++;
  }

  pre_exp += (exp * exp_sign);

  if (pre_exp <
      0)  // если exp отрицательная, то scale положительный, выравниваем scale
  {
    pre_exp = change_int_to_direct_code(pre_exp);
    tmp_result->scale = pre_exp;
    if (pre_exp > 28) {
      trimming_scale(tmp_result);
    }
  } else if (pre_exp > 0)  // если exp положительный, то scale отрицательный,
                           // выравниваем децимал
  {
    tmp_result->scale = 0;

    big_dec_pow_10(tmp_result, pre_exp);
  }
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error_code = 0;
  *dst = 0.0f;

  int64_t mantissa_bits = src.bits[0];
  int64_t scale_bits = src.bits[3] & GET_SCALE_MASK;
  int scale = (scale_bits >> 16) & 0xFF;

  long double mantissa = (long double)mantissa_bits;

  mantissa /= powl(10.0L, scale);

  if ((src.bits[3] & (1 << 31)) != 0) {
    mantissa = -mantissa;
  }

  *dst = (float)mantissa;

  return error_code;
}
