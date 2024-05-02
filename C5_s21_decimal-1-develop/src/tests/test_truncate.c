#include "test.h"

START_TEST(s21_truncate_1) {
  s21_decimal value_2 = {{0, 0, 0, 0x80020000}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_truncate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(value_2, value_1), 1);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal value_2 = {0};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(0.1111000, &value_2);
  int return_value = s21_truncate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, value_1), 1);
}
END_TEST

Suite *test_truncate(void) {
  Suite *s = suite_create("\033[45m-=S21_TRUNCATE=-\033[0m");
  TCase *tc = tcase_create("truncate_tc");

  tcase_add_test(tc, s21_truncate_1);
  tcase_add_test(tc, s21_truncate_2);
  suite_add_tcase(s, tc);
  return s;
}