CC = clang++ ## varaiant to school mac
CC1 = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TST_LIBS = -lgtest -lm -g
GCOV_LIBS = --coverage
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LTEST = $(shell pkg-config --libs --cflags gtest) ## varaiant to school mac
LTEST1 = -lgtest -lgtest_main  ## varaiant to other mac
# LIBO = s21_list.o
# NAME = s21_list.a
# NAME1 = s21_list1.a
BUILD_PATH = ./
EXE = test
TEST_SRC = qtests/s21_test*.c*
STYLE = clang-format --style=google

all: clean test

test1: clean 
	$(CC) $(CFLAGS) $(TEST_SRC) $(LTEST) -o $(EXE)  -pthread 
	./$(EXE) 

test: clean 
	$(CC1) $(CFLAGS) $(TEST_SRC) $(LTEST1) -o test -pthread 
	./$(EXE) 

style:
	@find s21_containers \( -name "*.c*" -or -name "*.h" \) -exec clang-format --style=google -i {} +
	@find qtests \( -name "*.c*" -or -name "*.h" \) -exec clang-format --style=google -i {} +
	@echo "All C++ source files and headers formatted with Google style."


rebuild:
	make all

clean:
	rm -rf *.o *.g* *.info *.out report *.a test *.log gcov* *.dSYM

valgrind: clean 
	$(CC1) $(CFLAGS) $(TEST_SRC) $(LTEST1) -o test -pthread 
	valgrind --tool=memcheck --leak-check=yes ./test

gcov_report: clean
	$(CC1) $(CFLAGS) $(GCOVFLAGS) -c $(TEST_SRC)
	$(CC1) $(CFLAGS) $(GCOVFLAGS) *.o $(LTEST1) -o $(EXE) -pthread
	./$(EXE)
	lcov --no-external -t "$(EXE)" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
