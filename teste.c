#include <stdio.h>
#include <string.h>
#include "fila_clientes.h"
#include "pilha_refeicao.h"

#define X_Burguer 0;
#define X_Salada 1;
#define Combo_1 2;
#define Combo_2 3;
#define Vegetariano 4;
#define Vegano 5;

char* cardapio[] = {  //define as refeicoes que serao util para checar o lanche e imprimi-lo na tela 
	[X_Burguer] = "pHQP";
	[X_Salada] = "pHSP";
	[Combo_1] = "pHQPFR";
	[Combo_2] = "pHSPFR";
	[Vegetariano] = "pQPFR";
	[Vegano] = "SFR";
};

int verifica_pedido(struct refeicao* topo, struct pedido* comeco){
	int i = 0;
	//enquanto o ingrediente no cardapio eh o mesmo no lanche, e nenhum dos dois chegou ao fim
	while ((topo != NULL) && (cardapio[comeco->num_refeicao][i] == topo->ingrediente)
				 && (i <= strlen(cardapio[comeco->num_refeicao])) - 1){
		i++;
		pop(topo);
	}

	//se ambos chegaram ao fim, sao iguais
	if ((topo == NULL) && (i == strlen(cardapio[comeco->num_refeicao] - 1)))
		return 1;
	return 0;
}

int imprime_pedidos(struct pedido* comeco){ //imprime os cinco primeiros pedidos da fila
	struct pedido* aux = comeco;

	for (int i = 1; i < 6; i++){
		printf("Pedido %d:\n", i);
		for (int j = 0; j < strlen(cardapio[aux->num_refeicao]); j++){
				printf("[%c] ", cardapio[aux->num_refeicao][j]);
		}
		printf("\n\n");
		aux = aux->prox;
	}
}