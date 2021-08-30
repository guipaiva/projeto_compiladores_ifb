#ifndef ERRORS_H
#define	ERRORS_H


/*
*@brief mostra uma mensagem de erro com formatação
*/
void error(char *s, ...);

/*
*@brief chamada para exibir mensagem sobre uma entrada esperada 
*/
void expected(char *s, ...);

/*
*@brief mostra uma mensagem de erro e encerra o programa
*/
void fatal(char *s);

/*
*@brief exibe uma mensagem sobre a referencia de um identificador
*não definid e encerra o programa 
*/
void undefined(char name);

/*
*@brief avisa sobre uma multideclaraçao de variável 
*/
void duplicated(char name);

/*
*@brief keyword não encontrada
*/
void unrecognized(char name);

/*
*@brief avisa a respeito de um identificador que nã é variável
*/
void notVar(char  name);


#endif