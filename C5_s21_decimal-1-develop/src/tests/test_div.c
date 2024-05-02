#include "test.h"

START_TEST(s21_div_1) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_div(value_1, value_2, &result);
  float result_float = 0;
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(fabs((result_float - 1)) < 1e-7, 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_div(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

// START_TEST(s21_div_4) {
//   s21_decimal value_2 = {0};
//   s21_decimal value_1 = {0};
//   s21_decimal result = {0};
//   int x = 2, y = 3;
//   s21_from_int_to_decimal(x, &value_1);
//   s21_from_int_to_decimal(y, &value_2);
//   int return_value = s21_div(value_1, value_2, &result);
//   float result_float = 0;
//   s21_from_decimal_to_float(result, &result_float);
//   ck_assert_int_eq(fabs((result_float - 0.66666)) < 1e-4, 1);
//   ck_assert_int_eq(return_value, 0);
// }
// END_TEST

START_TEST(s21_div_5) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};

  s21_decimal result = {0};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_6) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(0.1, &value_2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

Suite *test_div(void) {
  Suite *s = suite_create("\033[45m-=S21_DIV=-\033[0m");
  TCase *tc = tcase_create("div_tc");

  tcase_add_test(tc, s21_div_1);

  tcase_add_test(tc, s21_div_3);
  // tcase_add_test(tc, s21_div_4);
  tcase_add_test(tc, s21_div_5);
  tcase_add_test(tc, s21_div_6);
  suite_add_tcase(s, tc);
  return s;
}
