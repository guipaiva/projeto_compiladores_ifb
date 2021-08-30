#ifndef PARSER_H 
#define PARSER_H 
#include "../model/lista.h"

int labelCount;

list_t *symbol;

typedef struct variable{
	char *name;
	char *type;
	char *value;
}Var;

int newLabel();

void block();

void doRead();

void doWrite();

void factor();

void notFactor();

void term();

void expression();

void assignment();

void doIf();

void doWhile();

void boolTerm();

void boolExpression();

void relation();

void boolOr();

void boolXor();

void add();

void subtract();

void multiply();

void divide();

void *criaVar(void* data);

void initializeStruct(Var * var,char *name, char *type,char *value);

int locate(char *name);

void checkIdent();

int intable(char *name);

void checkTable(char *name);

void checkedUp(char *name);

void addSymbol(char *name,char *type);

void topDecls();

void decl();

void readVar();

#endif