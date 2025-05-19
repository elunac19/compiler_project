run:
	rm -f ./build/compiler
	gcc compiler.c -o build/compiler
	./build/compiler test.cpp