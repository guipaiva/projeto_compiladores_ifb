#include <ctype.h>
#include "parser.h"
#include "scanner.h"
#include "../input.h"
#include "../errors.h"
#include "../codegen.h"

void factor(){
	char name[MAX_NAME+1],num[MAX_NUM+1];
	if(lookahead== '('){
		match('(');
		expression();
		match(')');
	}else  if(isalpha(lookahead)){
		getName(name);
		asmLoadVariable(name);
	}else if(isdigit(lookahead)){
		getNum(num);
		asmLoadConstant(num);
	}else error("Unrecognized character: '%c'", lookahead);
}

void notFactor(){
	if(lookahead == '!'){
		match('!');
		factor();
		asmNot();
	}else factor();
}

void signedTerm(){
	char sign = lookahead;
	if(isAddOp(lookahead))nextChar();
	term();
	if(sign == '-')asmNegate();
}

void term(){
	notFactor();
	while(isMulOp(lookahead)){
		switch(lookahead){
			case'*':
				multiply();
				break;
			case '/':
				divide();
				break;
			case '&':
				boolAnd();
				break;
		}
	}
}

void expression(){
	signedTerm();
	while(isAddOp(lookahead)){
		switch(lookahead){
			case'+':
				add();
				break;
			case '-':
				subtract();
				break;
			case '|':
				boolOr();
				break;
			case '~':
				boolXor();
				break;
		}
	}
}

void assignment(){
	char name[MAX_NAME+1];
	getName(name);
	match('=');
	expression();
	asmStoreVariable(name);
}

void add(){
	match('+');
	asmPush();
	notFactor();
	asmPopAdd();
}

void subtract(){
	match('-');
	asmPush();
	notFactor();
	asmPopSub();
}

void boolOr(){
	match('|');
	asmPush();
	term();
	asmPopOr();
}

void boolXor(){
	match('~');
	asmPush();
	term();
	asmPopXor();
}

void multiply(){
	match('*');
	asmPush();
	notFactor();
	asmPopMul();
}

void divide(){
	match('/');
	asmPush();
	notFactor();
	asmPopDiv();
}

void boolAnd(){
	match('&');
	asmPush();
	notFactor();
	asmPopAnd();
}
