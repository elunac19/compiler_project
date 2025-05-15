run:
	rm -f ./compiler
	gcc compiler.c -o compiler
	./compiler test.cpp