#include "test.h"

START_TEST(s21_from_decimal_to_int_1) {
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 1, 0}};
  return_value = s21_from_decimal_to_int(value_1, &temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  int src = 0;
  int temp = 100;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_3) {
  int src = 0;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{MINUS, 0, 0, 0}};
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  int src = 133;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0x85, 0, 0, 0}};
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

Suite *test_from_decimal_to_int(void) {
  Suite *s = suite_create("\033[45m-=S21_FROM_DECIMAL_TO_INT=-\033[0m");
  TCase *tc = tcase_create("from_decimal_to_int_tc");

  tcase_add_test(tc, s21_from_decimal_to_int_1);
  tcase_add_test(tc, s21_from_decimal_to_int_2);
  tcase_add_test(tc, s21_from_decimal_to_int_3);
  tcase_add_test(tc, s21_from_decimal_to_int_4);

  suite_add_tcase(s, tc);
  return s;
}