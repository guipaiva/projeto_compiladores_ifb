#ifndef CRADDLE_H
#define CRADDLE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#define MAXNAME 30
#define MAXNUM 5
#define MAXTOKEN 60
#define MAXOP 2

#define SYMTBL_SZ 1000
#define KWLIST_SZ 4

char look;

char *symtbl[SYMTBL_SZ];
char *kwlist[KWLIST_SZ] = {"IF", "ELSE", "ENDIF", "END"};

const char *kwcode = "ilee";

int token;
char value[MAXTOKEN+1];
enum { KW_IF, KW_ELSE, KW_ENDIF, KW_END, TK_IDENT, TK_NUMBER, TK_OPERATOR };

/* protótipos */
void init();
void nextChar();
void error(char *fmt, ...);
void fatal(char *fmt, ...);
void expected(char *fmt, ...);
void match(char c);
void emit(char *fmt, ...);

void getName();
void getNum();
void getOp();


int isAddOp(char c);
int isMulOp(char c);
int isOp(char c);

void skipWhite();
void newLine();
void scan();
void skipComma();
int lookup(char *s, char *list[], int size);



#endif