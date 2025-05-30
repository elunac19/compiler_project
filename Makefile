.PHONY: clean test oop pp unit_test oop_test

clean: 
	rm -f ./build/oop
	rm -f ./build/oop2
	rm -f ./build/test
	rm -f ./build/unit_test
	rm -f ./build/test_runner

test:
	gcc compiler.c -o build/test
	./build/test ./test/test.cpp

oop:
	gcc compiler.c -o build/oop
	./build/oop ./test/oop.cpp

pp:
	gcc compiler.c -o build/oop2
	./build/oop2 ./test/pp.cpp

unit_test:
	mkdir -p build
	gcc -DTEST -I. -I./libs compiler-unit-test.c compiler.c libs/unity.c -o build/unit_test
	./build/unit_test

oop_test:
	mkdir -p build
	gcc -I. test_runner.c compiler.c -o build/test_runner
	./build/test_runner ./oop_valid ./oop_invalid
