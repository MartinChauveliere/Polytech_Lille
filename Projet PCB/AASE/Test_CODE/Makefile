#### Variables liées à la compilation ARM

CC_ARM=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS_ARM= -c -mcpu=$(MACH) -mthumb -std=gnu11 -O0 -Wall
LDFLAGS_ARM= -T stm32_ls.ld -nostdlib -Wl,-Map=final.map
OBJ_ARM=build/main.o build/functions.o build/stm32_startup.o

#### Variables liées à la compilation des tests unitaires

CC_TEST=gcc
OBJ_TEST=build/test_func.o build/unit_tests.o
CFLAGS_TEST= -W -Wall -g -Iincludes/# warnings

EXTRA_CFLAGS=-fprofile-arcs -ftest-coverage # utile pour calculer la couverture de code
EXTRA_LDFLAGS=--coverage # edition de liens avec couverture de code

TEST_SRC=tests/tests.c
TEST_OBJ=build/tests.o build/test_functions.o
TEST_EXEC=build/tri_tests
TEST_LDFLAGS=-lcheck -lpthread -lm
TEST_OS_DEP_LFLAGS= 

UNAME=$(shell uname)

ifeq ($(UNAME), Linux)
	TEST_OS_DEP_LFLAGS=-lsubunit -lrt
endif


all: final.elf test.elf

##COMPILATION ARM

build/main.o:src/main.c
	$(CC_ARM) $(CFLAGS_ARM) -c $< -o $@

build/functions.o:src/functions.c
	$(CC_ARM) $(CFLAGS_ARM) -c $< -o $@

build/stm32_startup.o:src/stm32_startup.c
	$(CC_ARM) $(CFLAGS_ARM) -c $< -o $@

final.elf: $(OBJ_ARM)
	$(CC_ARM) $(LDFLAGS_ARM) $^ -o $@

##COMPILATION TEST

build/test_func.o:src/functions.c
	$(CC_TEST) $(CFLAGS_TEST) $(EXTRA_CFLAGS) -c $^ -o $@

build/unit_tests.o:test/unit_tests.c
	$(CC_TEST) $(CFLAGS_TEST) $(EXTRA_CFLAGS) -c $^ -o $@

test.elf: $(OBJ_TEST)
	$(CC_TEST) $(OBJ_TEST) $(TEST_LDFLAGS) $(EXTRA_LDFLAGS) $(TEST_OS_DEP_LFLAGS) -o $@

##LOAD IN BOARD

load:
	openocd -f board.cfg

##COVERAGE

coverage:
	./test.elf
	gcov -o build -f -b build/test*
	lcov --directory build --base-directory . -c -o cov.info
	genhtml cov.info

##CLEAN

clean:
	rm -rf *.elf
	rm -rf build/*.o  build/*.gcda  build/*.gcno


