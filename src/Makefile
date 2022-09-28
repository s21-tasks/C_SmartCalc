CC=gcc
SRC=c_files/calc.c
OBJ=c_files/calc.o
SRC_T=c_files/tests.c
OBJ_T=c_files/tests.o
 CFLAGS=-Wall -Werror -Wextra --coverage
TESTFLAGS=-lcheck -lm -lpthread -lgcov

all: tests gcov_report install

gcov_report: tests
	lcov -t "otchet" -o otchet.info -c -d ./c_files
	genhtml -o report otchet.info 

tests: lib.a $(OBJ_T) $(OBJ)
	$(CC) $(CFLAGS) lib.a $(OBJ_T) $(OBJ) $(TESTFLAGS) -o test
	./test

lib.a: $(OBJ)
	ar rcs lib.a $(OBJ)

install:
	mkdir -p build
	cd ./build; cmake ../qt_calc/CMakeLists.txt; make
	./build/qt_calc.app/Contents/MacOS/qt_calc

uninstall:
	rm -rf build-qt_calc-Desktop_x86_darwin_generic_mach_o_64bit-Debug
	rm -rf qt_calc/CMakeLists.txt.user
	rm -rf CMakeFiles
	rm -rf build/*

debug: $(SRC) c_files/main.c
	$(CC) -Wall -Wextra $^
	./a.out

clean:
	rm -rf c_files/*.o 
	rm -rf c_files/*.gc*
	rm -rf c_files/*.a
	rm -f test
	rm -rf a.out *.a
	rm -rf report/*
	rm -rf otchet.info
	rm -rf build/.*
dvi:
	open ../README_RUS.md
dist:
	tar -cvf archive.tar ../src