#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "scanner.h"
#include "asmCode.h"
#include "../model/lista.h"
#include "../view/errors.h"
#include "../view/output.h"

int newLabel(){
	return labelCount++;
}

void block(){
	int follow = 0;
	do{
		scan();
		switch(token){
			case 'i':
				doIf();
				break;
			case 'w':
				doWhile();
				break;
			case 'W':
				doWrite();
				break;
			case 'R':
				doRead();
				break;
			case 'e':
			case 'l':
				follow = 1;
				break;
			case 'x':
				assignment();
				break;
		}
		if(!follow)semiColon();
	}while(!follow);
}

void doRead(){
	nextToken();
	matchString("(");
	for(;;){
		readVar();
		if(token != ',')break;
		nextToken();
	}
	matchString(")");
}

void doWrite(){
	nextToken();
	matchString("(");
	for(;;){
		expression();
		asm_write();
		if(token !=',')break;
		nextToken();
	}
	matchString(")");
}

void factor(){
	if(token == '('){
		nextToken();
		boolExpression();
		matchString(")");
	}else{
		if(token == 'x'){
			if(!intable(value))undefined(value);
			asm_loadvar(value);
		}
		else if(token == '#')asm_loadconst(value);
		else expected("Math Factor");
		nextToken();
	}
}

void notFactor(){
	if(token == '!'){
		nextToken();
		relation();
		asm_not();
	}else relation();
}

void term(){
	factor();
	while(isMulOp(token)){
		asm_push();
		switch(token){
			case '*':
				multiply();
				break;
			case '/':
				divide();
				break;
		}
	}
}

void expression(){
	if(isAddOp(token))asm_clear();
	else term();

	while(isAddOp(token)){
		asm_push();
		switch(token){
			case '+':
				add();
				break;
			case '-':
				subtract();
				break;
		}
	}
}

void assignment(){
	char name[MAX_TOKEN+1];
	strcpy(name,value);
	checkTable(name);
	nextToken();
	matchString("=");
	boolExpression();
	asm_store(name);
}

void doIf(){
	int l1,l2;
	nextToken();
	boolExpression();
	l1 = newLabel();
	l2 = l1;

	asm_jmpfalse(l1);
	block();
	if(token  == 'l'){
		nextToken();
		l2 = newLabel();
		asm_jmp(l2);
		printf("L%d<br>\n",l1);
		block();
	}
	emit("L%d<br>\n",l2);
	matchString("ENDIF");
}

void doWhile(){
	int l1,l2;
	nextToken();
	l1 = newLabel();
	l2 = newLabel();

	printf("L%d<br>\n",l1);
	boolExpression();
	asm_jmpfalse(l2);
	block();
	matchString("ENDWHILE");
	asm_jmp(l1);
	printf("L%d<br>\n",l2);
}

void boolTerm(){
	notFactor();
	while(token == '&'){
		asm_push();
		nextToken();
		notFactor();
		asm_popand();
	}
}

void boolExpression(){
	boolTerm();
	while(isOrOp(token)){
		asm_push();
		switch(token){
			case '|':
				boolOr();
				break;
			case '~':
				boolXor();
				break;
		}
	}
}

void relation(){
	char op;
	expression();
	if(isRelOp(token)){
		op = token;
		nextToken();
		if(op == '<'){
			if(token == '>'){
				nextToken();
				op = '#';
			}else if(token == '='){
				nextToken();;
				op = 'L';
			}
		}else if(op == '>' && token == '='){
			nextToken();
			op = 'G';
		}
		asm_push();
		expression();
		asm_popcompare();
		asm_relop(op,newLabel(),newLabel());
	}
}

void boolOr(){
	nextToken();
	boolTerm();
	asm_popor();
}

void boolXor(){
	nextToken();
	boolTerm();
	asm_popxor();
}

void add(){
	nextToken();
	term();
	asm_popadd();
}

void subtract(){
	nextToken();
	term();
	asm_popsub();
}

void multiply(){
	nextToken();
	factor();
	asm_popmul();
}

void divide(){
	nextToken();
	factor();
	asm_popdiv();
}


void *criaVar(void* data){
    void* ptr = malloc(sizeof(Var));
    memcpy(ptr,data,sizeof(Var));
    return ptr;
}

void destructorVar(void* data){
    free(data);
}

void checkIdent(){
	if(token != 'x')expected("Identifier");
}

int intable(char *name){
	int i;
	Var *var;
	iterador aux = symbol->raiz;
	for(i=0;i<symbol->size;i++){
		var = aux->data;
		if(strcmp(var->name,name)==0)return i+1;
		aux = aux->prox; 
	}
	return -1;
}

int locate(char *name){
	return intable(name);
}

void checkTable(char *name){
	if (!intable(name))undefined(name);
}

void checkedUp(char *name){
	if(intable(name)>-1)duplicated(name);
}

void initializeStruct(Var *var,char *name, char *type,char *value){
	var->name = malloc(sizeof(char)*(strlen(name)+1));
	var->type = malloc(sizeof(char)*(strlen(type)+1));
	var->value = malloc(sizeof(char)*(strlen("NULL")+1));
	strcpy(var->name,name);
	strcpy(var->type,name);
	strcpy(var->value,value);
}

void addSymbol(char *name,char *type){
	Var var;
	checkedUp(name);
	initializeStruct(&var,name,type,"NULL\0");
	listInsere(symbol,&var);
}

void topDecls(){
	scan();
	while(token == 'v'){
		do{
			decl();
		}while(token == ',');
		semiColon();
	}
}

void decl(){
	nextToken();
	if(token !='x')expected("Var name");
	checkedUp(value);
	addSymbol(value,"v");
	allocVar(value,0);
	nextToken();
}

void readVar(){
	checkIdent();
	checkTable(value);
	asm_read(value);
	nextToken();
}

