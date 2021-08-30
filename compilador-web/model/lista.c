#include <stdlib.h>
#include <stdio.h>

#include "lista.h"

void listaInit(list_t **list,fn_aloca_var constructor){
	(*list)=malloc(sizeof(list_t));
	(*list)->raiz=NULL;
	(*list)->folha=NULL;
	(*list)->constructor=constructor;
	(*list)->size=0;
}

listNode * listaNovo(void *data,fn_aloca_var constructor){
	listNode *newNode = malloc(sizeof(listNode));
	newNode->data=constructor(data);
	newNode->prox=NULL;
	return newNode;
}

void listInsere(list_t *list, void *data){
	listNode *newNode=listaNovo(data,list->constructor);
	newNode->prox=list->raiz;
	if(listaVazia(list)==0){
		list->folha=newNode;
	}
	list->raiz=newNode;
	list->size++;
}

size_t listaVazia(list_t *list){
	return list->size == 0;
}