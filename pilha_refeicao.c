#include <stdio.h>
#include <stdlib.h>
#include "pilha_refeicao.h"

struct refeicao{
	char ingrediente;
	struct refeicao* anterior;
};

void inicializa_preparo(){
	struct refeicao* topo = NULL;
}

struct refeicao* novo_ingrediente(char ingrediente){
	struct refeicao* novo;
	novo = malloc(sizeof(struct refeicao));
	novo->anterior = NULL;
	novo->ingrediente = ingrediente;

	return novo;
}

void push(struct refeicao* novo, struct refeicao* topo, char ingrediente){
	novo_ingrediente(ingrediente);

	if (topo == NULL){
		topo = novo;
	} else {
		novo->anterior = topo;
		topo = novo;
	}
}

void pop(struct refeicao* topo){
	struct refeicao* aux = topo;

	topo = topo->anterior;
	free(aux);
}

void escreve_pilha(struct refeicao* topo){
	struct refeicao* aux = topo;

	while (aux != NULL){
		printf("%d ", aux->ingrediente);

		aux = aux->anterior;
	}
}

void destroi_refeicao(struct refeicao* topo){
	while (topo != NULL)
		pop(topo);
}