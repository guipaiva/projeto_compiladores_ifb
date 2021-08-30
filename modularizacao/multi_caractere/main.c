#include <stdio.h>
#include "scanner.h"
#include "parser.h"
#include "../input.h"
#include "../output.h"
#include "../errors.h"

int main(){
	//char name[MAX_NAME+1], num[MAX_NUM+1];
	initInput();
	assignment();
	/*getName(name);
	printf("%s\n",name);
	match('=');
	getNum(num);
	printf("%s\n",num);
	match('+');
	getName(name);
	printf("%s\n",name);*/
	return 0;
}