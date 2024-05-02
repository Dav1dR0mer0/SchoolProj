s21_grep:
	gcc -std=c11 -pedantic -Wall -Werror -Wextra s21_grep.c s21_grep.h -o s21_grep
	clang-format -style=Google -i ../../src/cat/*.c *.h
test:
	sh test_grep.sh
style:
	clang-format -style=Google -n *.c *.h
	clang-format -style=Google -i *.c *.h

clean:
	rm s21_grep
	clear
	
leaks:	s21_grep
	leaks -atExit -- ./s21_cat -lovei testfile1.txt
	
valgrind:
	cd ../.. && cd materials/build/valgrind && bash run.sh