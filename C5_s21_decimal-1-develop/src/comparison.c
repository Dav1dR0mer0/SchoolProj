#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_2, value_1);
}

int s21_is_greater(s21_decimal value_1,
                   s21_decimal value_2) {  // 1 == 1>2; 0 == else  // decimal
  int result = 0;
  s21_big_decimal value_1_big = dec_to_big_dec(value_1);
  s21_big_decimal value_2_big = dec_to_big_dec(value_2);

  normalization(&value_1_big, &value_2_big);

  if (value_1_big.sign == value_2_big.sign)  // проверка на знак
  {
    if (CHECK_BITS_EQUAL) {
      result = 0;
    } else if (value_1_big.sign && value_2_big.sign) {
      result = !greater_not(&value_1_big, &value_2_big);
    } else {
      result = (greater_not(&value_1_big, &value_2_big));
    }
  } else if (value_1_big.sign) {
    result = 0;
  } else {
    if (CHECK_BITS_NULL) {
      result = 0;
    } else {
      result = 1;
    }
  }
  return result;  // 0 - FALSE 1 - TRUE
}

int greater_not(s21_big_decimal *value_1_big, s21_big_decimal *value_2_big) {
  int result = 0;
  int i = 6;
  int ALARM = 0;
  while ((i >= 0) && ALARM == 0) {
    if (value_1_big->bits[i] > value_2_big->bits[i]) {
      result = 1;
      ALARM = 1;
    } else if (value_1_big->bits[i] < value_2_big->bits[i]) {
      result = 0;
      ALARM = 1;
    }
    i--;
  }

  return result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal value_1_big = dec_to_big_dec(value_1);
  s21_big_decimal value_2_big = dec_to_big_dec(value_2);
  int result = 0;
  if (CHECK_BITS_NULL) {
    result = 1;
  } else if (value_1_big.sign == value_2_big.sign)  // знаки одинаковые
  {
    normalization(&value_1_big, &value_2_big);
    if (CHECK_BITS_EQUAL) {
      result = 1;
    } else {
      result = 0;
    }
  } else {
    result = 0;
  }

  return result;  // 0 - FALSE 1 - TRUE
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  if (s21_is_equal(value_1, value_2) || s21_is_greater(value_1, value_2)) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  if (s21_is_equal(value_1, value_2) || s21_is_less(value_1, value_2)) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
}
