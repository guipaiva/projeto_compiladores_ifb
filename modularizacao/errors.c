#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include "errors.h"


void error(char *s, ...){
	va_list args;
	fputs("Error: ", stderr);
	va_start(args, s);
	vfprintf(stderr, s, args);
	va_end(args);
	fputc('\n', stderr);
	exit(1);
}

void expected(char *s, ...){
	va_list args;
	fputs("Error: ", stderr);
	va_start(args, s);
	vfprintf(stderr, s, args);
	va_end(args);
	fputs(" expected!\n", stderr);
	exit(1);
}

/*
void fatal(char *s){
	error(s);
}

void undefined(char name){
	fprintf(stderr, "Error: Undefined identifier %c\n", name);
	exit(1);
}

void duplicated(char name){
	fprintf(stderr, "Error: Duplicated identifier %c\n", name);
	exit(1);
}

void unrecognized(char name){
	fprintf(stderr, "Error: Unrecognized keyword %c\n", name);
	exit(1);
}

void notVar(char  name){
	fprintf(stderr, "Error: %c is not a variable\n",name);
}*/