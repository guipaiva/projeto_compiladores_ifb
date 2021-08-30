#ifndef SCANNER_H
#define SCANNER_H

#define MAX_TOKEN 16
#define KWLIST_SZ 9

char lookahead,token, value[MAX_TOKEN+1];
int labelCount;

void nextToken();

void skipComment();

void skipWhite();

void semiColon();

void scan();

void getName();

void getNum();

void getOp();

void matchString(char *s);

int isAddOp(char c);

int isMulOp(char c);

int isOrOp(char c);

int isRelOp(char c);

#endif