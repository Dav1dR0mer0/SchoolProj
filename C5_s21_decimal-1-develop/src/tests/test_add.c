#include "test.h"

START_TEST(s21_add_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(
      result.bits[0] + result.bits[1] + result.bits[2] + result.bits[3], 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{1, 1, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int x = 10, y = 10, z = 20, result_int = 0;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_int_to_decimal(y, &value_2);
  int return_value = s21_add(value_1, value_2, &result);
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, z);
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result;
  int x = 10, y = 10, z = 20, result_int = 0;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_int_to_decimal(y, &value_2);
  int return_value = s21_add(value_1, value_2, &result);
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, z);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{0xFFFFFFF1, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(result.bits[0], 4294967282);
  ck_assert_uint_eq(result.bits[1], 4294967295);
  ck_assert_uint_eq(result.bits[2], 4294967295);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal value_1 = {{1, 1, 1, MINUS}};
  s21_decimal value_2 = {{0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_add_666) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0x00080000}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_8) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {{1, 1, 1, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(s21_add_9) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{7, 0, 0, MINUS}};
  s21_decimal result = {0};
  int z;
  int return_value = s21_add(value_1, value_2, &result);
  s21_from_decimal_to_int(result, &z);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(z, -5);
}
END_TEST

START_TEST(s21_add_10) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{7, 0, 0, 0}};
  s21_decimal result = {0};
  // int z;
  int return_value = s21_add(value_1, value_2, &result);
  // s21_from_decimal_to_int(result, &z);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(
      result.bits[0] + result.bits[1] + result.bits[2] + result.bits[3], 9);
}
END_TEST

START_TEST(s21_add_11) {
  s21_decimal value_1 = {{1, 2, 3, 0}};
  s21_decimal value_2 = {{9, 8, 7, 0}};
  s21_decimal result = {0};
  // int z;
  int return_value = s21_add(value_1, value_2, &result);
  // s21_from_decimal_to_int(result, &z);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(
      result.bits[0] + result.bits[1] + result.bits[2] + result.bits[3], 30);
}
END_TEST

START_TEST(s21_add_12) {
  s21_decimal value_1 = {{1, 4, 8, 0x00080000}};
  s21_decimal value_2 = {{1, 3, 3, 0x00070000}};
  s21_decimal result = {{11, 34, 38, 0x00080000}};
  // int z;
  int return_value = s21_add(value_1, value_2, &result);
  // s21_from_decimal_to_int(result, &z);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(result.bits[0], 11);
  ck_assert_uint_eq(result.bits[1], 34);
  ck_assert_uint_eq(result.bits[2], 38);
  ck_assert_uint_eq(result.bits[3], 0x00080000);
}
END_TEST

START_TEST(s21_add_13) {
  s21_decimal value_1 = {{1, 4, 8, 0x00140000}};
  s21_decimal value_2 = {{1, 3, 3, 0x00100000}};
  s21_decimal result = {0};
  // int z;
  int return_value = s21_add(value_1, value_2, &result);
  // s21_from_decimal_to_int(result, &z);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(result.bits[0], 10001);
  ck_assert_uint_eq(result.bits[1], 30004);
  ck_assert_uint_eq(result.bits[2], 30008);
  ck_assert_uint_eq(result.bits[3], 1310720);
}
END_TEST

START_TEST(s21_add_14) {
  s21_decimal value_1 = {{1, 4, 8, 0x00040000}};
  s21_decimal value_2 = {{1, 3, 3, 0x00000000}};
  s21_decimal result = {0};
  // int z;
  int return_value = s21_add(value_1, value_2, &result);
  // s21_from_decimal_to_int(result, &z);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(result.bits[0], 10001);
  ck_assert_uint_eq(result.bits[1], 30004);
  ck_assert_uint_eq(result.bits[2], 30008);
  ck_assert_uint_eq(result.bits[3], 262144);
}
END_TEST

Suite *test_add(void) {
  Suite *s = suite_create("\033[45m-=S21_ADD=-\033[0m");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, s21_add_1);
  tcase_add_test(tc, s21_add_2);
  tcase_add_test(tc, s21_add_3);
  tcase_add_test(tc, s21_add_4);
  tcase_add_test(tc, s21_add_5);
  tcase_add_test(tc, s21_add_6);
  tcase_add_test(tc, s21_add_666);
  tcase_add_test(tc, s21_add_7);
  tcase_add_test(tc, s21_add_8);
  tcase_add_test(tc, s21_add_9);
  tcase_add_test(tc, s21_add_10);
  tcase_add_test(tc, s21_add_11);
  tcase_add_test(tc, s21_add_12);
  tcase_add_test(tc, s21_add_13);
  tcase_add_test(tc, s21_add_14);
  suite_add_tcase(s, tc);
  return s;
}