#include "test.h"

int main(void) {
  int failed = 0;

  Suite *s21_decimal_test[] = {test_add(),
                               test_sub(),
                               test_mul(),
                               test_div(),
                               test_is_less(),
                               test_is_less_or_equal(),
                               test_is_greater(),
                               test_is_greater_or_equal(),
                               test_is_equal(),
                               test_is_not_equal(),
                               test_from_int_to_decimal(),
                               test_from_float_to_decimal(),
                               test_from_decimal_to_int(),
                               test_from_decimal_to_float(),
                               test_floor(),
                               test_round(),
                               test_truncate(),
                               test_negate(),
                               NULL};

  for (int i = 0; s21_decimal_test[i] != NULL; ++i) {
    SRunner *sr = srunner_create(s21_decimal_test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  (failed > 0)
      ? printf("\033[41m========== TESTS FAILED: %d ==========\033[0m\n",
               failed)
      : printf("\033[42m========== TESTS FAILED: %d ==========\033[0m\n",
               failed);
  return 0;
}