.PHONY: clean test oop pp

clean: 
	rm -f ./build/oop
	rm -f ./build/oop2
	rm -f ./build/test

test:
	gcc compiler.c -o build/test
	./build/test ./test/test.cpp

oop:
	gcc compiler.c -o build/oop
	./build/oop ./test/oop.cpp

pp:
	gcc compiler.c -o build/oop2
	./build/oop2 ./test/pp.cpp
