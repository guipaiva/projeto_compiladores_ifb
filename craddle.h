#ifndef CRADDLE_H
#define CRADDLE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>


char look;

/* protótipos */
void init();
void nextChar();
void error(char *fmt, ...);
void fatal(char *fmt, ...);
void expected(char *fmt, ...);
void match(char c);
char getName();
char getNum();
void emit(char *fmt, ...);
int isAddOp(char c);
int isMulOp(char c);
void skipWhite();
void newLine();


#endif