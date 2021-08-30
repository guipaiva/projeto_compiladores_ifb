#include<ctype.h>
#include "scanner.h"
#include "../input.h"
#include "../errors.h"

void getName(char *name){
	int i;
	if(!isalpha(lookahead)) expected("Identifier or Keyword");
	for(i=0;isalnum(lookahead);i++){
		if(i>=MAX_NAME)error("Identifier too long.");
		name[i] = toupper(lookahead);
		nextChar();
	}
	name[i]='\0';
	//skipWhite();
}

void getNum(char *num){
	int i;
	if(!isdigit(lookahead)) expected("Integer");
	for(i=0;isdigit(lookahead);i++){
		if(i>=MAX_NUM)error("Integer too long.");
		num[i] =lookahead;
		nextChar();
	}
	num[i]='\0';
	//skipWhite();
}

/*long getNum(){
	long num = 0;
	if(!isdigit(lookahead))expected("Integer");
	do{
		num *= 10;
		num += look - '0';
		nextChar();                       
	}while(isdigit(lookahead));
	return num;
}*/

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
	return (c == '-' || c == '+' ||c== '|' || c==  '~');
}

int isMulOp(char c){
	return (c == '*' || c == '/' || c == '&');
}