#ifndef SCANNER1_H
#define SCANNER1_H

/*
*@brief verifca se o nome de um indetificador ou palavra-chave é alfabético
*/
char getName();

/*
*@brief verifica se lookahead é um número
*/
char getNum();

/*
*@brief verifica se a entrada dá match com o esperado, chamand expected c.c.
*/
void match(char c);


/*
*@brief verifica se o caractere analisado é um operador de soma ou subtração
*/
int isAddOp(char c);

/*
*@brief verifica se o caractere analisado é um operador de multiplicação ou divisão
*/
int isMulOp(char c);

#endif