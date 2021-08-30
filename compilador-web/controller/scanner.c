#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "scanner.h"
#include "../model/input.h"
#include "../view/errors.h"

char *kwlist[KWLIST_SZ] = {"IF","ELSE","ENDIF","WHILE","ENDWHILE","VAR","END","READ","WRITE"};
char kwcode[KWLIST_SZ+1] = "ileweveRW";

void nextToken(){
	skipWhite();
	if(isalpha(lookahead))getName();
	else if(isdigit(lookahead))getNum();
	else getOp();	
}

void skipComment(){
	while(lookahead != '}'){
		nextChar();
		if(lookahead == '{')skipComment();
	}
	nextChar();
}

void skipWhite(){
	while (isspace(lookahead) || lookahead  == '{'){
		if(lookahead == '{')skipComment();
		else nextChar();
	}	
}

void semiColon(){
	if(token ==  ';')nextToken();
}

void scan(){
	int kw=0,i,j=-1;
	if(token == 'x'){
		for(i=0;i<KWLIST_SZ;i++){
			if(strcmp(kwlist[i],value)==0){
				j=i;
				break;
			}
		}
		kw = j;
		if(kw >=0)token = kwcode[kw];
	}
} 

void getName(){
	int i;
	skipWhite();

	if(!isalpha(lookahead)) expected("Identifier or Keyword");
	for(i=0;isalnum(lookahead) && i<MAX_TOKEN;i++){
		value[i] = toupper(lookahead);
		nextChar();
	}
	value[i] =  '\0';
	token = 'x';
}

void getNum(){
	skipWhite();
	int i;

	if(!isdigit(lookahead)) expected("Integer");

	for(i=0;isdigit(lookahead) && i<MAX_TOKEN;i++){
		value[i] =  lookahead;
		nextChar();
	}
	value[i] = '\0';
	token  = '#';
}

void getOp(){
	skipWhite();
	token = lookahead;
	value[0] = lookahead;
	value[1] =  '\0';
	nextChar();
}

void matchString(char *s){
	if(strcmp(value,s)!=0)expected(s);
	nextToken();
}

int isAddOp(char c){
	return (c == '-' || c == '+');
}

int isMulOp(char c){
	return (c == '*' || c == '/');
}

int isOrOp(char c){
	return (c == '|' || c == '~');
}

int isRelOp(char c){
	return (strchr("=#<>",c)!=NULL);
}