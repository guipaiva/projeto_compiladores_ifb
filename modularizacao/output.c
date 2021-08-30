#include <stdio.h>
#include<stdarg.h>
#include "output.h"

void emit(char *s, ...){
	va_list args;
	putchar('\t');
	va_start(args, s);
	vprintf(s, args);
	va_end(args);
	putchar('\n');
}