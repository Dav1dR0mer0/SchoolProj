#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0;
  set_bits_zero(result, 1);  // set_bits_zero работает корректно

  s21_big_decimal value_1_big = dec_to_big_dec(value_1);
  s21_big_decimal value_2_big = dec_to_big_dec(value_2);
  s21_big_decimal tmp_result = {0};

  normalization(&value_1_big, &value_2_big);

  if (value_1_big.sign == value_2_big.sign)  // val_1 минус, а val_2 минус
  {
    normalization(&value_1_big, &value_2_big);

    tmp_result = dec_sum(&value_1_big, &value_2_big);
    if (value_1_big.sign) {
      tmp_result.sign = value_1_big.sign;
    }

  } else if (value_1_big.sign &&
             !value_2_big.sign)  // val_1 минус, а val_2 плюс
  {
    if (greater_not(&value_2_big, &value_1_big)) {
      tmp_result = dec_sub(&value_2_big, &value_1_big);
      tmp_result.sign = 0;
    } else if (greater_not(&value_1_big, &value_2_big)) {
      tmp_result = dec_sub(&value_1_big, &value_2_big);
      tmp_result.sign = 1u;
    }
    // в ином случае - нас одинаковые числа, и ответ равен 0, знак плюсу =0
  } else if (!value_1_big.sign &&
             value_2_big.sign)  // val_1 плюс, а val_2 минус
  {
    if (greater_not(&value_1_big, &value_2_big)) {
      tmp_result = dec_sub(&value_1_big, &value_2_big);
      tmp_result.sign = 0;
    } else if (greater_not(&value_2_big, &value_1_big)) {
      tmp_result = dec_sub(&value_2_big, &value_1_big);
      tmp_result.sign = 1u;
    }
    // в ином случае - нас одинаковые числа, и ответ равен 0, знак плюсу =0
  }

  if (CHECK_SIZE_BIG_DEC || (tmp_result.scale > 28)) {
    while (CHECK_SIZE_BIG_DEC && tmp_result.scale) {
      bank_rounding(&tmp_result);
    }
    while (tmp_result.scale > 28) {
      bank_rounding(&tmp_result);
    }
  }
  if (CHECK_SIZE_BIG_DEC) {
    if (value_1_big.sign) {
      error_code = 2;
    } else {
      error_code = 1;
    }
  }
  *result = big_dec_to_dec(tmp_result);
  return error_code;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0;
  set_bits_zero(result, 1);

  s21_big_decimal value_1_big = dec_to_big_dec(value_1);
  s21_big_decimal value_2_big = dec_to_big_dec(value_2);
  s21_big_decimal tmp_result = {0};

  normalization(&value_1_big, &value_2_big);

  if (value_1_big.sign &
      value_2_big.sign)  // -М - (-Б) = Б - М ИЛИ -Б - (-М) = -(Б - М)
  {
    if (greater_not(&value_1_big, &value_2_big)) {
      tmp_result = dec_sum(&value_1_big, &value_2_big);
      tmp_result.sign = 1u;
    } else if (greater_not(&value_2_big, &value_1_big)) {
      value_2_big.sign = 0;
      tmp_result = dec_sub(&value_2_big, &value_1_big);
      tmp_result.sign = 0;
    }

  } else if (value_1_big.sign &&
             !value_2_big
                  .sign)  // -М - (+Б) ИЛИ -Б - (+М) == - (Б + М или М + Б)
  {
    tmp_result = dec_sum(&value_1_big, &value_2_big);
    tmp_result.sign = 1u;
  } else if (!value_1_big.sign &&
             value_2_big.sign)  // М - (-Б) = Б+М ИЛИ Б - (-М) = Б+М
  {
    tmp_result = dec_sub(&value_2_big, &value_1_big);
    tmp_result.sign = 0;
  } else if (!value_1_big.sign &&
             !value_2_big.sign)  // М - Б = -(Б - М)  ИЛИ  Б - М
  {
    if (greater_not(&value_1_big, &value_2_big)) {
      tmp_result = dec_sub(&value_1_big, &value_2_big);
      tmp_result.sign = 1;
    } else if (greater_not(&value_2_big, &value_1_big)) {
      value_2_big.sign = 0;
      tmp_result = dec_sub(&value_2_big, &value_1_big);
      tmp_result.sign = 1u;
    }
  }

  if (CHECK_SIZE_BIG_DEC || (tmp_result.scale > 28)) {
    while (CHECK_SIZE_BIG_DEC && tmp_result.scale) {
      bank_rounding(&tmp_result);
    }
    while (tmp_result.scale > 28) {
      bank_rounding(&tmp_result);
    }
  }
  if (CHECK_SIZE_BIG_DEC) {
    if (value_1_big.sign) {
      error_code = 2;
    } else {
      error_code = 1;
    }
  }
  *result = big_dec_to_dec(tmp_result);

  return error_code;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0;
  set_bits_zero(result, 1);

  s21_big_decimal value_big_1 = dec_to_big_dec(value_1);
  s21_big_decimal value_big_2 = dec_to_big_dec(value_2);
  s21_big_decimal tmp_result = {0};

  tmp_result.sign = value_big_1.sign ^ value_big_2.sign;

  unsigned long long int ovf = 0;
  for (int i = 0; i < 3; i++) {
    tmp_result.bits[i] = value_big_1.bits[0] * value_big_2.bits[i] + ovf;
    ovf = (tmp_result.bits[i] & GET_OVF_MASK) >> 32;

    tmp_result.bits[i + 1] =
        value_big_1.bits[1] * value_big_2.bits[i + 1] + ovf;
    ovf = (tmp_result.bits[i + 1] & GET_OVF_MASK) >> 32;

    tmp_result.bits[i + 2] =
        value_big_1.bits[2] * value_big_2.bits[i + 2] + ovf;
    ovf = (tmp_result.bits[i + 2] & GET_OVF_MASK) >> 32;
  }

  tmp_result.scale = value_big_1.scale + value_big_2.scale;

  if (CHECK_SIZE_BIG_DEC || (tmp_result.scale > 28)) {
    while (CHECK_SIZE_BIG_DEC && tmp_result.scale) {
      bank_rounding(&tmp_result);
    }
    while (tmp_result.scale > 28) {
      bank_rounding(&tmp_result);
    }
  }

  if (CHECK_SIZE_BIG_DEC) {
    if (tmp_result.sign) {
      error_code = 2;
    } else {
      error_code = 1;
    }
  }

  *result = big_dec_to_dec(tmp_result);

  return error_code;
}

s21_big_decimal dec_sub(s21_big_decimal *value_big_1,
                        s21_big_decimal *value_big_2) {
  s21_big_decimal result = {0};
  uint64_t borrow = 0;
  uint64_t diff = 0;

  for (int i = 6; i >= 0; --i) {
    diff = value_big_1->bits[i] - value_big_2->bits[i] - borrow;
    result.bits[i] = (diff & 0xFFFFFFFF);
    borrow = (diff < value_big_2->bits[i]) || (borrow && diff == 0);
  }

  result.scale = value_big_1->scale;

  return result;
}

s21_big_decimal dec_sum(s21_big_decimal *value_big_1,
                        s21_big_decimal *value_big_2) {
  s21_big_decimal result = {0};

  result.bits[0] =
      result.bits[0] | (value_big_1->bits[0] + value_big_2->bits[0]);

  result.bits[1] =
      result.bits[1] | (value_big_1->bits[1] + value_big_2->bits[1]);

  result.bits[2] =
      result.bits[2] | (value_big_1->bits[2] + value_big_2->bits[2]);

  result.bits[3] =
      result.bits[3] | (value_big_1->bits[3] + value_big_2->bits[3]);

  result.bits[4] =
      result.bits[4] | (value_big_1->bits[4] + value_big_2->bits[4]);

  result.bits[5] =
      result.bits[5] | (value_big_1->bits[5] + value_big_2->bits[5]);

  result.bits[6] =
      result.bits[6] | (value_big_1->bits[6] + value_big_2->bits[6]);

  get_and_set_ovf(&result);
  // округли если надо

  result.scale = value_big_1->scale;
  return result;
}

int big_dec_pow_10(s21_big_decimal *value_big_1, unsigned long int power) {
  int error_code = 0;

  for (unsigned long long int i = 0; i < power; i++) {
    value_big_1->bits[0] = value_big_1->bits[0] * 10;

    value_big_1->bits[1] = value_big_1->bits[1] * 10;

    value_big_1->bits[2] = value_big_1->bits[2] * 10;

    value_big_1->bits[3] = value_big_1->bits[3] * 10;

    value_big_1->bits[4] = value_big_1->bits[4] * 10;

    value_big_1->bits[5] = value_big_1->bits[5] * 10;

    value_big_1->bits[6] = value_big_1->bits[6] * 10;

    get_and_set_ovf(value_big_1);
  }

  return error_code;
}

unsigned long long int big_dec_div_remn_by_10(s21_big_decimal *value_big_1) {
  unsigned long long int remnant = 0;
  for (int i = 6; i >= 0; i--) {
    value_big_1->bits[i] += remnant << 32;
    remnant = value_big_1->bits[i] % 10;
    value_big_1->bits[i] /= 10;
  }

  get_and_set_ovf(value_big_1);
  return remnant;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  set_bits_zero(result, 1);
  int error_code = 0;
  s21_big_decimal tmp_result = {0};
  s21_big_decimal value_big_1 = dec_to_big_dec(value_1);
  s21_big_decimal value_big_2 = dec_to_big_dec(value_2);
  tmp_result.sign = value_big_1.sign ^ value_big_2.sign;
  if ((value_2.bits[0] + value_2.bits[1] + value_2.bits[2]) == 0) {
    error_code = 3;
  } else if ((value_1.bits[0] + value_1.bits[1] + value_1.bits[2]) == 0) {
    // ну типо ответ равен нулю, что и делает set_bits_zero(result, 1);
  } else if (s21_is_equal(value_1, value_2)) {
    tmp_result.bits[0] = 1u;
  } else {
    div_normalization(&value_big_1, &value_big_2);
    error_code = dec_div(&value_big_1, &value_big_2, &tmp_result);
  }

  *result = big_dec_to_dec(tmp_result);

  return error_code;
}

int dec_div(s21_big_decimal *numerator, s21_big_decimal *denominator,
            s21_big_decimal *tmp_result) {
  int error_code = 0;

  unsigned int pow_of_tmp_denominator = 0;
  s21_big_decimal tmp_denominator = *denominator;
  unsigned long long int quotient = 0;

  while (greater_not(numerator, &tmp_denominator) &&
         !(CHECK_BITS_EQUAL_POITER)) {
    big_dec_pow_10(&tmp_denominator, 1);
    pow_of_tmp_denominator++;

  }  // добираемся до числа

  while ((greater_not(numerator, denominator)) && !error_code &&
         (pow_of_tmp_denominator > 0))  // цикл деления для целой части ответа
  {
    big_dec_div_remn_by_10(
        &tmp_denominator);  // уменьшаем делитель, чтобы начать новое
                            // вычитание(если можем)
    pow_of_tmp_denominator--;

    while (greater_not(numerator, &tmp_denominator) ||
           (CHECK_BITS_EQUAL_POITER)) {
      *numerator = dec_sub(numerator, &tmp_denominator);
      quotient++;
    }
    if (quotient) {
      big_dec_set_quotient(tmp_result, &quotient, pow_of_tmp_denominator);
      if (tmp_result->bits[3] || tmp_result->bits[4] || tmp_result->bits[5] ||
          tmp_result->bits[6]) {
        if (tmp_result->sign == 1) {
          error_code = 2;
        } else {
          error_code = 1;
        }
      }
    }
  }

  if (!CHECK_NUM_BITS_NULL && !error_code)  //  деление для дробной части ответа
  {
    fractional_div(numerator, *denominator, tmp_result);
  }

  // !!! после всех плясок в конце делаем проверку на слишком малое число
  return error_code;
}

int big_dec_set_quotient(s21_big_decimal *tmp_result,
                         unsigned long long int *quotient,
                         unsigned int pow_of_tmp_denominator) {
  s21_big_decimal calque = {0};
  int error_code = 0;
  calque.bits[0] += *quotient;
  big_dec_pow_10(&calque, pow_of_tmp_denominator);

  if (tmp_result->sign == 1) {
    *tmp_result = dec_sum(tmp_result, &calque);
    tmp_result->sign = 1;
  } else {
    *tmp_result = dec_sum(tmp_result, &calque);
    tmp_result->sign = 0;
  }

  *quotient = 0;
  return error_code;
}

void fractional_div(s21_big_decimal *numerator, s21_big_decimal tmp_denominator,
                    s21_big_decimal *tmp_result) {
  unsigned long long int quotient = 0;
  unsigned int stop_div = 0;
  tmp_result->scale = 0;
  big_dec_pow_10(numerator, 1);
  tmp_result->scale++;
  while (!CHECK_NUM_BITS_NULL && !stop_div) {
    while (greater_not(&tmp_denominator, numerator)) {
      big_dec_pow_10(numerator, 1);

      big_dec_pow_10(tmp_result, 1);
      tmp_result->scale++;
    }

    while (greater_not(numerator, &tmp_denominator) ||
           (CHECK_BITS_EQUAL_POITER)) {
      *numerator = dec_sub(numerator, &tmp_denominator);
      quotient++;
    }
    if (quotient) {
      s21_big_decimal calque = {0};

      calque.bits[0] += quotient;
      big_dec_pow_10(tmp_result, 1);

      *tmp_result = dec_sum(tmp_result, &calque);

      quotient = 0;
    }
    if (tmp_result->bits[3] || tmp_result->bits[4] || tmp_result->bits[5] ||
        tmp_result->bits[6]) {
      stop_div = 1;
      trimming_scale(tmp_result);
    }
  }
}
