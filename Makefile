test:
	rm -f ./build/test
	gcc compiler.c -o build/test
	./build/test test.cpp

oop:
	rm -f ./build/oop
	gcc compiler.c -o build/oop
	./build/oop oop.cpp

oop2:
	rm -f ./build/oop2
	gcc compiler.c -o build/oop2
	./build/oop2 oop2.cpp
	