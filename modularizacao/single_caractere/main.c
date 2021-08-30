#include <stdio.h>
#include "../input.h"
#include "../output.h"
#include "../errors.h"
#include "scanner1.h"

int main(){
	initInput();
	printf("%c\n",getName());
	match('=');
	printf("%c\n",getNum());
	match('+');
	printf("%c\n",getName());
}