CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11 -pedantic
#LINUX_FLAGS=-lsubunit -lrt -lpthread -lm



s21_cat:
	$(CC) $(FLAGS) *.c *.h -o s21_cat
test:
	sh test_cat.sh
style:
	clang-format -style=Google -n ../../src/cat/*.c *.h
	clang-format -style=Google -i ../../src/cat/*.c *.h
clean:
	rm s21_cat
	clear
leaks: s21_cat
	leaks -atExit -- ./s21_cat -benstv testfile1.txt

valgrind:
	cd ../.. && cd materials/build/valgrind && bash run.sh