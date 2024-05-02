#include "test.h"

START_TEST(s21_from_float_to_decimal_1) {
  float src = 0.0000000;
  s21_decimal value_1 = {{0xffffff, 0xffffff, 0xffffff, 0xffffff}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &value_1);
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

// START_TEST(s21_from_float_to_decimal_2)
// {
// 	float src = 1.23456789999;
// 	float temp = 0;
// 	int return_value = 0;
// 	s21_decimal value_1 = {0};
// 	return_value = s21_from_float_to_decimal(src, &value_1);
// 	s21_from_decimal_to_float(value_1, &temp);
// 	ck_assert_float_eq_tol(src, temp, 1e-06);
// 	ck_assert_int_eq(return_value, 0);
// }
// END_TEST

// START_TEST(s21_from_float_to_decimal_3)
// {
// 	float src = 7.92281625143e+27f;
// 	float temp = 0;
// 	int return_value = 0;
// 	s21_decimal value_1 = {{0, 0, 0, 0}};
// 	return_value = s21_from_float_to_decimal(src, &value_1);
// 	s21_from_decimal_to_float(value_1, &temp);
// 	ck_assert_float_eq_tol(7922816.0f, temp, 1e-06);
// 	ck_assert_int_eq(return_value, 0);
// }
// END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  float src = 7.922816;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  return_value = s21_from_float_to_decimal(src, &value_1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

// START_TEST(s21_from_float_to_decimal_5)
// {
// 	float src = 7.92281577919e+28;
// 	float temp = 0;
// 	int return_value = 0;
// 	s21_decimal value_1 = {{0, 0, 0, 0}};
// 	s21_from_float_to_decimal(src, &value_1);
// 	s21_from_decimal_to_float(value_1, &temp);
// 	ck_assert_float_eq_tol(7922816.0f, temp, 1e-06);
// 	ck_assert_int_eq(return_value, 0);
// }
// END_TEST

START_TEST(s21_from_float_to_decimal_6) {
  float src = 234.15;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  return_value = s21_from_float_to_decimal(src, &value_1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *test_from_float_to_decimal(void) {
  Suite *s = suite_create("\033[45m-=S21_FROM_FLOAT_TO_DECIMAL=-\033[0m");
  TCase *tc = tcase_create("from_float_to_decimal_tc");

  tcase_add_test(tc, s21_from_float_to_decimal_1);
  // tcase_add_test(tc, s21_from_float_to_decimal_2);
  // tcase_add_test(tc, s21_from_float_to_decimal_3);
  tcase_add_test(tc, s21_from_float_to_decimal_4);
  // tcase_add_test(tc, s21_from_float_to_decimal_5);
  tcase_add_test(tc, s21_from_float_to_decimal_6);
  suite_add_tcase(s, tc);
  return s;
}