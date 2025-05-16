run:
	rm -f ./compiler
	gcc compiler.c -o build/compiler
	./build/compiler test.cpp