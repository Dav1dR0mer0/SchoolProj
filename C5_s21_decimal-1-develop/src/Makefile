# all, clean, test, s21_decimal.a, gcov_report
GCC=gcc -g
CFALGS=-Wall -Werror -Wextra -std=c11
SOURCES=*.c
TESTS_SOURCES=tests/test.c tests/test_floor.c tests/test_round.c tests/test_truncate.c tests/test_negate.c tests/test_from_float_to_decimal.c tests/test_is_equal.c tests/test_is_greater.c tests/test_is_greater_or_equal.c tests/test_is_less.c tests/test_is_less_or_equal.c tests/test_from_decimal_to_int.c tests/test_from_int_to_decimal.c tests/test_is_not_equal.c tests/test_mul.c tests/test_div.c tests/test_add.c tests/test_sub.c tests/test_from_decimal_to_float.c
OBJECTS=$(SOURCES:.c=.o)

ifeq ($(shell uname), Linux)
	CHECKFLAGS=-lcheck -lm -lpthread -lrt -lsubunit
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif

all: clean s21_decimal.a
	
s21_decimal.a:
	$(GCC) $(CFALGS) s21_decimal.h s21_arithmetic.c s21_servants.c transform.c comparison.c truncate.c negate.c round.c floor.c -c
	ar rcs s21_decimal.a $(OBJECTS)

test: clean s21_decimal.a
	$(GCC) $(CFALGS) $(TESTS_SOURCES) s21_decimal.a $(CHECKFLAGS) -o s21_decimal
	./s21_decimal

gcov_report: clean s21_decimal.a
	$(GCC) $(CFALGS) $(TESTS_SOURCES) s21_decimal.h s21_arithmetic.c s21_servants.c transform.c comparison.c truncate.c negate.c round.c floor.c s21_decimal.a $(CHECKFLAGS) -fprofile-arcs -ftest-coverage -lgcov -o s21_decimal
	./s21_decimal
	lcov -t "./s21_decimal" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html

clean:
	rm -rf s21_decimal *.a $(OBJECTS) a.out *.gcno *.gcda report report.info *.dSYM

valgrind: clean test
	valgrind --tool=memcheck --leak-check=yes  ./s21_decimal

clang:
	clang-format -i -style=google s21_decimal.h s21_arithmetic.c s21_servants.c transform.c comparison.c tests/*.c tests/*.h

main: clean
	$(GCC) $(CFALGS) s21_decimal.h s21_arithmetic.c s21_servants.c transform.c comparison.c $(CHECKFLAGS) -o s21_decimal
	./s21_decimal
