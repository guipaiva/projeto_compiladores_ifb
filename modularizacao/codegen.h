#ifndef CODEGEN_H
#define	CODEGEN_H

/*
*@brief gera um código assembly para carregar uma constante no registrador primário
*/
void asmLoadConstant(char *s);

/*
*@brief traduz o  código para carregar uma variável no registrador primário
*/
void asmLoadVariable(char *s);

/*
*@brief inverte sinal do valor no registrador primário
*/
void asmNegate();

/*
*@brief traduz código para colocar o valor do registrador primário na pilha
*/
void asmPush();

/*
*@brief  remove o valor do topo da  pilha  e soma com o valor do registraidor primario
*/
void asmPopAdd();

/*
*@brief  subtrai o valor do registraidor primario do valor no topo da pilha
*/
void asmPopSub();

/* 
*@brief multiplica valor no topo da pilha pelo valor no registrador primário
*/
void asmPopMul();

/*
@brief divide valor no topo da pilha pelo valor no registrador primário
*/
void asmPopDiv();

/*
*@brief armazena valor do registrador primário em &name
*/
void asmStoreVariable(char *name);

/*
*@brief TRADUZ cálculo de "OU" entre o elemento do topo da pilha e o registrador primário
*/
void asmPopOr();

/*
*@brief TRADUZ cálculo de "OU-EXCLUSIIVO" entre o elemento do topo da pilha e o registrador primário
*/
void asmPopXor();

/*
*@brief TRADUZ cálculo de "AND" entre o elemento do topo da pilha e o registrador primário
*/
void asmPopAnd();

/*
*@brief nega o valor do regitrador primário
*/
void asmNot();
#endif