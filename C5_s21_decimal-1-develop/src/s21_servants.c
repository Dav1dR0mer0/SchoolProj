#include "s21_decimal.h"

void set_bits_zero(void *dst, int type) {
  if (type == 1) {
    s21_decimal *destination = (s21_decimal *)dst;
    destination->bits[0] = destination->bits[1] = destination->bits[2] =
        destination->bits[3] = 0;
  }
  // if (type == 2) {
  //   s21_big_decimal *destination = (s21_big_decimal *)dst;
  //   destination->bits[0] = destination->bits[1] = destination->bits[2] =
  //       destination->bits[3] = destination->bits[4] = destination->bits[5] =
  //           destination->bits[6] = destination->bits[7] =
  //           destination->bits[8] =
  //               0;
  // }
}

unsigned long int get_sign(const s21_decimal *patient) {
  return (((1u << 31) & (patient->bits[3])) != 0);
}

unsigned long int get_raw_scale(s21_decimal *patient) {
  unsigned long int raw_scale = (patient->bits[3] & GET_SCALE_MASK) >> 16;
  return raw_scale;
}

s21_big_decimal dec_to_big_dec(s21_decimal val_1) {
  s21_big_decimal converted_dec = {0};

  converted_dec.bits[0] = val_1.bits[0];
  converted_dec.bits[1] = val_1.bits[1];
  converted_dec.bits[2] = val_1.bits[2];
  converted_dec.sign = get_sign(&val_1);
  converted_dec.scale = get_raw_scale(&val_1);

  return converted_dec;
}
s21_decimal big_dec_to_dec(s21_big_decimal val_1) {
  s21_decimal converted_dec = {0};
  converted_dec.bits[0] = val_1.bits[0];
  converted_dec.bits[1] = val_1.bits[1];
  converted_dec.bits[2] = val_1.bits[2];
  converted_dec.bits[3] =
      converted_dec.bits[3] | (val_1.scale << 16) | (val_1.sign << 31);

  return converted_dec;
}

void normalization(s21_big_decimal *value_big_1, s21_big_decimal *value_big_2) {
  if (value_big_1->scale < value_big_2->scale) {
    big_dec_pow_10(value_big_1, value_big_2->scale - value_big_1->scale);
    value_big_1->scale = value_big_2->scale;
  } else if (value_big_2->scale < value_big_1->scale) {
    big_dec_pow_10(value_big_2, value_big_1->scale - value_big_2->scale);
    value_big_2->scale = value_big_1->scale;
  }
}

int bank_rounding(s21_big_decimal *dst) {
  int error_code = 0;
  unsigned long long int remnant = big_dec_div_remn_by_10(dst);

  if ((dst->bits[0] % 10) % 2 && remnant > 4) {
    dst->bits[0] += 1;
    get_and_set_ovf(dst);
  } else if (!((dst->bits[0] % 10) % 2) && remnant > 5) {
    dst->bits[0] += 1;
    get_and_set_ovf(dst);
  }

  dst->scale -= 1;
  return error_code;
}

void get_and_set_ovf(s21_big_decimal *dst) {
  unsigned long long int ovf = 0;
  for (int i = 0; i < 7; i++) {
    ovf = (dst->bits[i] & GET_OVF_MASK) >> 32;
    // printf("овф %d: %lld\n", i, ovf);
    dst->bits[i + 1] = dst->bits[i + 1] + ovf;
    dst->bits[i] = dst->bits[i] & 0xffffffff;
  }
}

int check_ovf(s21_big_decimal *patient) {
  int result = patient->bits[3] + patient->bits[4] + patient->bits[5] +
               patient->bits[6] + patient->bits[7];

  return result;  // число отличное от нуля - переполнен big_dec, 0 - не
                  // переполнен
}

int trimming_scale(s21_big_decimal *dst) {
  int error_code = 0;
  while (((check_ovf(dst) && dst->scale)) || dst->scale > 28) {
    error_code = bank_rounding(dst);
  }
  return error_code;
}

int div_normalization(s21_big_decimal *numerator,
                      s21_big_decimal *denominator) {
  int error_code = 0;

  int scale_dif = numerator->scale - denominator->scale;

  if (scale_dif > 0) {
    big_dec_pow_10(denominator, scale_dif);
  } else if (scale_dif < 0) {
    scale_dif = change_int_to_direct_code(scale_dif);

    big_dec_pow_10(numerator, scale_dif);
  }

  return error_code;
}
