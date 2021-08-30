#include <stdio.h>
#include <stdarg.h>
#include "output.h"

void header(){
	printf(".model small\n<br>");
	printf(".stack\n<br>");
	printf(".code\n<br>");
	printf("extrn READ:near, WRITE:near\n<br>");
	printf("PROG segment byte public\n<br>");
	printf("\tassume cs:PROG,ds:PROG,es:PROG,ss:PROG\n<br>");
}

void prolog(){
	printf("MAIN:\n<br>");
	printf("\tmov ax, PROG\n<br>");
	printf("\tmov ds, ax\n<br>");
	printf("\tmov es, ax\n<br>");
}

void epilog(){
	printf("\tmov ax, 4C00h\n<br>");
	printf("\tint 21h\n<br>");
	printf("PROG ends\n<br>");
	printf("\tend MAIN\n<br>");
}

void emit(char *s, ...){
	va_list args;
	putchar('\t');
	va_start(args, s);
	vprintf(s, args);
	va_end(args);
	putchar('\n');
}