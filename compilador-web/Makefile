all: init cgi clean

init: library
	gcc main.c -o compilador libTiny.a 

library: list tiny 
	ar rcs libTiny.a lista.o asmCode.o errors.o input.o output.o parser.o scanner.o

list: model/lista.c model/lista.h
	gcc -c model/lista.c 

tiny: controller/asmCode.c controller/asmCode.h view/errors.c view/errors.h model/input.c model/input.h view/output.c view/output.h controller/parser.c controller/parser.h controller/scanner.c controller/scanner.h
	gcc -c controller/asmCode.c view/errors.c model/input.c view/output.c controller/parser.c controller/scanner.c

clean:
	clear
	rm -rf *.o *.a

cgi:
	cp compilador /usr/lib/cgi-bin/compilador
	
