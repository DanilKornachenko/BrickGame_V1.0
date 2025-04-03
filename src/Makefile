OS := $(shell uname)

backend := brick_game/tetris/
CC := gcc -std=c11
CFLAGS := -Wall -Werror -Wextra
NAME := tetris

.PHONY: all install uninstall test clean purge gcov_report dvi dist

all: install run

install:
				mkdir -p build
				mkdir -p build/game
				mkdir -p build/game/bin
				$(CC) $(CFLAGS) -c $(backend)tetris.c -lncurses -o build/game/bin/$(NAME).o
				ar r build/game/$(NAME).a build/game/bin/*.o

uninstall:
				rm -rf build/game/*.a
				rm -rf build/game/*.out

run:
				$(CC) $(CFLAGS) $(backend)/main.c build/game/$(NAME).a gui/cli/cli.c -lncurses -o build/game/game.out
				./build/game/game.out

test:
				mkdir -p test/game
				$(CC) $(CFLAGS) $(backend)tetris.c test/*.c -lncurses -lcheck -o test/game/test.out
				./test/game/test.out

clean:
				rm -rf build
				rm -f test/game/test.out
				rm -rf report
				rm -f test/game/*
				rm -rf brick_gameV1.tar.gz

purge: uninstall clean

gcov_report: test
ifeq ($(OS), Linux)
				$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(backend)tetris.c test/*.c -lncurses -lcheck -o test/game/test.out
				-./test/game/test.out
				lcov -t "gcov_report" -o tests.info -c -d .
				genhtml -o report tests.info
				rm -f *.gcno *.gch *.info report.out *.gcov
				xdg-open report/index.html
endif
ifeq ($(OS), Darwin)
				$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(backend)tetris.c test/*.c -lncurses -lcheck -o test/game/test.out
				-./test/game/test.out
				lcov -t "gcov_report" -o tests.info -c -d .
				genhtml -o report tests.info
				rm -f *.gcno *.gch *.info report.out *.gcov
				open report/index.html
endif

clang-n:
				cp ../materials/linters/.clang-format ./
				clang-format -n brick_game/tetris/*.c
				clang-format -n brick_game/tetris/*.h
				clang-format -n gui/cli/*.c
				clang-format -n gui/cli/*.h
				clang-format -n test/unit_test.c
				rm .clang-format

clang-i:
				cp ../materials/linters/.clang-format ./
				clang-format -i brick_game/tetris/*.c
				clang-format -i brick_game/tetris/*.h
				clang-format -i gui/cli/*.c
				clang-format -i gui/cli/*.h
				clang-format -i test/unit_test.c
				rm .clang-format

dist:
				tar -czvf brick_gameV1.tar.gz $(backend) gui/cli test save Makefile

dvi:
ifeq ($(OS), Linux)
				xdg-open dvi/KA_brickgame.jpg
endif
ifeq ($(OS), Darwin)
				open dvi/KA_brickgame.jpg
endif
