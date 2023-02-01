#include <stdio.h>
#include "fila_clientes.h"

struct pedido{
	int cliente;
	int num_refeicao;
	struct pedido* prox;
	struct pedido* anterior;
}

void inicializa_fila(){
	struct pedido* comeco = NULL;
	struct pedido* fim = NULL;
}

int fila_vazia(struct pedido* comeco, struct pedido* fim){
	if ((comeco == NULL) && (fim == NULL)){
		printf("Não há elementos na lista.\n");
		return 1;
	}

	return 0;
}

struct pedido* cria_pedido(){
	struct pedido* novo;
	novo->prox = NULL;
	novo->anterior = NULL;
	
	printf("Informe o valor do novo elemento");
	scanf("%d", novo->cliente);

	return novo;
}

void insere_fim(struct pedido* comeco, struct pedido* fim){
	struct pedido* novo = create_node();

	if (fila_vazia(comeco, fim) == 1){
		comeco = novo;
		fim = novo;
	} else {
		//adiciona o novo cliente e atualiza o ponteiro para o fim
		novo->prox = fim;
		fim->prox = novo;
		fim = novo;
	}
}

void retira_comeco(struct pedido* comeco){
	struct pedido* aux = comeco;

	comeco->anterior->prox = NULL;
	comeco->anterior = NULL;
	comeco = comeco->anterior;

	free(aux);
}