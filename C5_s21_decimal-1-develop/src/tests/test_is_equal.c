#include "test.h"

START_TEST(s21_is_equal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_equal_3) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, MINUS}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_4) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{20, 0, 0, 0x10000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_5) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, MINUS}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_6) {
  s21_decimal value_1 = {{0, 24234, 76634, 0}};
  s21_decimal value_2 = {{0, 66434, 3455, MINUS}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_equal_7) {
  s21_decimal value_1 = {{0, 3453, 0756, 0}};
  s21_decimal value_2 = {{0, 3453, 0756, 0}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_8) {
  s21_decimal value_1 = {{0, 3453, 0756, MINUS}};
  s21_decimal value_2 = {{0, 3453, 0756, 0}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *test_is_equal(void) {
  Suite *s = suite_create("\033[45m-=S21_IS_EQUAL=-\033[0m");
  TCase *tc = tcase_create("is_equal_tc");

  tcase_add_test(tc, s21_is_equal_1);
  tcase_add_test(tc, s21_is_equal_2);
  tcase_add_test(tc, s21_is_equal_3);
  tcase_add_test(tc, s21_is_equal_4);
  tcase_add_test(tc, s21_is_equal_5);
  tcase_add_test(tc, s21_is_equal_6);
  tcase_add_test(tc, s21_is_equal_7);
  tcase_add_test(tc, s21_is_equal_8);
  suite_add_tcase(s, tc);
  return s;
}