#ifndef PARSER_H
#define	PARSER_H

/*
*@brief analisa e traduz um fator matemático/booleano
*/
void factor();

/*
*@brief analisa e traduz um fator com NOT opcional
*/
void notFactor();

/*
*@brief analisa e traduz um termo com um sinal
*/
void signedTerm();

/*
*@brief analisa e traduz um termo
*/
void term();

/*
*@brief analisa e traduz uma expressão
*/
void expression();

/*
*@brief analisa e traduz um comando  de atribuição
*/
void assignment();

/*
@brief analisa e traduz a operação soma
*/
void add();

/*
@brief analisa e traduz a operação subtração
*/
void subtract();

/*
*@brief reconhece e traduz um "OR"
*/
void boolOr();

/*
*@brief reconhece e traduz um "XOR"
*/
void boolXor();

/*
@brief analisa e traduz a operação multiplicação
*/
void multiply();

/*
@brief analisa e traduz a operação divisão
*/
void divide();

/*
*@brief reconhece e traduz um "AND"
*/
void boolAnd();
#endif