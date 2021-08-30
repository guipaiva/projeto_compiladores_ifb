#include<ctype.h>
#include "../input.h"
#include "../errors.h"
#include "scanner1.h"

char getName(){
	char name;
	if(!isalpha(lookahead)) expected("Identifier or Keyword");
	name  = toupper(lookahead);
	nextChar();
	//skipWhite();
	return name;
}

char getNum(){
	char num;
	if(!isdigit(lookahead)) expected("Integer");
	num = lookahead;
	nextChar();
	return num;
}

void match(char c){
	if(lookahead != c)expected("'%c'",c);
	nextChar();
	/*char s[2];
	if(lookahead != c){
		s[0] = c;
		s[1] =  '\0';
		expected(s);
	}
	nextChar();
	skipWhite();*/
}


int isAddOp(char c){
	return (c == '-' || c == '+');
}

int isMulOp(char c){
	return (c == '*' || c == '/');
}