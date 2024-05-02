

// dst: Часто используется для обозначения "destination" (целевого объекта) в
// контексте функций копирования или перемещения данных. src: Часто используется
// для обозначения "source" (исходного объекта) в контексте функций копирования
// или перемещения данных. val: Часто используется для обозначения "value"
// (значения). idx: Часто используется для обозначения "index" (индекса). len:
// Часто используется для обозначения "length" (длины). ptr: Часто используется
// для обозначения "pointer" (указателя). arr: Часто используется для
// обозначения "array" (массива). str: Часто используется для обозначения
// "string" (строки). err: Часто используется для обозначения "error" (ошибки).
// ret: Часто используется для обозначения "return" (возвращаемого значения).
// patient: Переменная над которой производится работу но сама она не
// изменяется(извлечение значения итд) В Decimal каждая фукнция у нас имеет тип
// int, чтобы можно было словить ошибку и вернуть ее Правила морфизма имен -
// префикс отвечает за состояние переменной во времени - new,original,final...
// value -> new_value суффикс отвечает за изменение сути переменной, по типу
// превращения переменной в другой тип данных value -> value_big

#ifndef _SRC_S21_DECIMAL_H_
#define _SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GET_SCALE_MASK 0b00000000111111110000000000000000
#define SET_SIGN_MASK 0x8000000000000000
#define GET_OVF_MASK 0xFFFFFFFF00000000
#define OVF_DIGIT 0x0000000100000000

//==============================
#define MAX_INT 2147483647
#define MIN_INT -2147483648
#define MINUS 0x80000000
//==============================

#define CHECK_SIZE_BIG_DEC                                           \
  (tmp_result.bits[3] || tmp_result.bits[4] || tmp_result.bits[5] || \
   tmp_result.bits[6])

#define CHECK_BITS_NULL                                               \
  ((value_1_big.bits[6] + value_1_big.bits[5] + value_1_big.bits[4] + \
    value_1_big.bits[3] + value_1_big.bits[2] + value_1_big.bits[1] + \
    value_1_big.bits[0] + value_2_big.bits[6] + value_2_big.bits[5] + \
    value_2_big.bits[4] + value_2_big.bits[3] + value_2_big.bits[2] + \
    value_2_big.bits[1] + value_2_big.bits[0]) == 0)
#define CHECK_NUM_BITS_NULL                                        \
  ((numerator->bits[6] + numerator->bits[5] + numerator->bits[4] + \
    numerator->bits[3] + numerator->bits[2] + numerator->bits[1] + \
    numerator->bits[0]) == 0)

#define CHECK_BITS_EQUAL                              \
  (value_1_big.bits[6] == value_2_big.bits[6]) &&     \
      (value_1_big.bits[5] == value_2_big.bits[5]) && \
      (value_1_big.bits[4] == value_2_big.bits[4]) && \
      (value_1_big.bits[3] == value_2_big.bits[3]) && \
      (value_1_big.bits[2] == value_2_big.bits[2]) && \
      (value_1_big.bits[1] == value_2_big.bits[1]) && \
      (value_1_big.bits[0] == value_2_big.bits[0])
#define CHECK_BITS_EQUAL_POITER                          \
  (numerator->bits[6] == tmp_denominator.bits[6]) &&     \
      (numerator->bits[5] == tmp_denominator.bits[5]) && \
      (numerator->bits[4] == tmp_denominator.bits[4]) && \
      (numerator->bits[3] == tmp_denominator.bits[3]) && \
      (numerator->bits[2] == tmp_denominator.bits[2]) && \
      (numerator->bits[1] == tmp_denominator.bits[1]) && \
      (numerator->bits[0] == tmp_denominator.bits[0])

typedef struct {
  unsigned long int bits[4];

} s21_decimal;

typedef struct {
  unsigned long long int bits[7];
  unsigned long int sign;
  unsigned long int scale;

} s21_big_decimal;

// s21_servants
void set_bits_zero(void *dst, int type);
unsigned long int get_sign(const s21_decimal *patient);
unsigned long int get_raw_scale(s21_decimal *patient);
s21_big_decimal dec_to_big_dec(s21_decimal val_1);
s21_decimal big_dec_to_dec(s21_big_decimal val_1);
void normalization(s21_big_decimal *val_1, s21_big_decimal *val_2);
s21_big_decimal dec_sum(s21_big_decimal *value_big_1,
                        s21_big_decimal *value_big_2);
int trimming_scale(s21_big_decimal *dst);
int check_ovf(s21_big_decimal *patient);
void get_and_set_ovf(s21_big_decimal *dst);
int bank_rounding(s21_big_decimal *dst);
int div_normalization(s21_big_decimal *numerator, s21_big_decimal *denominator);

// s21_arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int big_dec_pow_10(s21_big_decimal *value_big_1, unsigned long int power);

s21_big_decimal dec_sub(s21_big_decimal *value_big_1,
                        s21_big_decimal *value_big_2);
s21_big_decimal dec_sum(s21_big_decimal *value_big_1,
                        s21_big_decimal *value_big_2);

unsigned long long int big_dec_div_remn_by_10(s21_big_decimal *value_big_1);

int dec_div(s21_big_decimal *numerator, s21_big_decimal *denominator,
            s21_big_decimal *tmp_result);
void fractional_div(s21_big_decimal *numerator, s21_big_decimal tmp_denominator,
                    s21_big_decimal *tmp_result);
int big_dec_set_quotient(s21_big_decimal *tmp_result,
                         unsigned long long int *quotient,
                         unsigned int pow_of_tmp_denominator);

// comparison
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int greater_not(s21_big_decimal *big_value_1, s21_big_decimal *big_value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// transform
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
void f_to_dec_set_mant_sign_and_scale(float *src, s21_big_decimal *dst_big);
int change_int_to_direct_code(int dst);
int Take_Scale(s21_decimal num);
double Convert_From_Bin_To_Num(s21_decimal src);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int change_int_to_additional_code(int dst);

// truncate
int s21_truncate(s21_decimal value, s21_decimal *result);

// negate
int s21_negate(s21_decimal value, s21_decimal *result);

// round
int s21_round(s21_decimal value, s21_decimal *result);

// floor
int s21_floor(s21_decimal value, s21_decimal *result);

///
void chek_error_code(s21_big_decimal *tmp_result, int *error_code);

#endif  // _SRC_S21_DECIMAL_H_
