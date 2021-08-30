#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>

typedef void* (*fn_aloca_var)(void*);

typedef struct listNode{
	void *data;
	struct listNode *prox;
}listNode;

typedef struct  list_t{
	listNode *raiz;
	listNode *folha;
	fn_aloca_var constructor;
	size_t size;
}list_t;

typedef listNode *iterador;

void listaInit(list_t **list,fn_aloca_var constructor);

listNode * listaNovo(void *data,fn_aloca_var constructor);

void listInsere(list_t *list, void *data);

size_t listaVazia(list_t *list);

#endif