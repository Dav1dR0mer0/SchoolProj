#include "test.h"

START_TEST(s21_mul_1) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_mul(value_2, value_1, &result), result_int = 0;
  ck_assert_int_eq(return_value, 0);
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(s21_mul_2) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_mul(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_mul_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_mul(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(s21_mul_4) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {{2, 0, 0, 0x00070000}};
  s21_decimal result = {0};
  int return_value = s21_mul(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *test_mul(void) {
  Suite *s = suite_create("\033[45m-=S21_MUL=-\033[0m");
  TCase *tc = tcase_create("mul_tc");

  tcase_add_test(tc, s21_mul_1);
  tcase_add_test(tc, s21_mul_2);
  tcase_add_test(tc, s21_mul_3);
  tcase_add_test(tc, s21_mul_4);
  suite_add_tcase(s, tc);
  return s;
}