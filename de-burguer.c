#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "de-burguer.h"

void inicializa_fila(struct pedido* comeco, struct pedido* fim, int* num_clientes){
	insere_fim(comeco, fim, num_clientes);
	insere_fim(comeco, fim, num_clientes);
	insere_fim(comeco, fim, num_clientes);
}

int fila_vazia(struct pedido* comeco, struct pedido* fim){
	if ((comeco == NULL) && (fim == NULL)){
		printf("Não há elementos na lista.\n");
		return 1;
	}

	return 0;
}

struct pedido* cria_pedido(int* num_clientes){
	struct pedido* novo;
	novo->prox = NULL;
	novo->anterior = NULL;
	novo->cliente = (num_clientes++);
	novo->num_refeicao = rand()%6;

	return novo;
}

void insere_fim(struct pedido* comeco, struct pedido* fim, int* num_clientes){
	struct pedido* novo = cria_pedido(num_clientes);

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

struct refeicao* novo_ingrediente(char ingrediente){
	struct refeicao* novo;
	novo = malloc(sizeof(struct refeicao));
	novo->anterior = NULL;
	novo->ingrediente = ingrediente;

	return novo;
}

void push(struct refeicao* topo, char ingrediente){
	struct refeicao* novo = novo_ingrediente(ingrediente);

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

int move_direita(struct refeicao* topo, struct refeicao* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais* elementos_mapa){
//verifica se o personagem esta tentando "subir" em uma estacao, se sim, faz o que ela pede e retorna o inteiro 1, se nao retorna 0

	if ((elementos_mapa->chapeiro.lin == elementos_mapa->hamburguer.lin) && (elementos_mapa->chapeiro.col + 1 == elementos_mapa->hamburguer.col)){
		push(topo, elementos_mapa->hamburguer.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->pao_cima.lin) && (elementos_mapa->chapeiro.col + 1 == elementos_mapa->pao_cima.col)){
		push(topo, elementos_mapa->pao_cima.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->pao_baixo.lin) && (elementos_mapa->chapeiro.col + 1 == elementos_mapa->pao_baixo.col)){
		push(topo, elementos_mapa->pao_baixo.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->queijo.lin) && (elementos_mapa->chapeiro.col + 1 == elementos_mapa->queijo.col)){
		push(topo, elementos_mapa->queijo.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->salada.lin) && (elementos_mapa->chapeiro.col + 1 == elementos_mapa->salada.col)){
		push(topo, elementos_mapa->salada.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->fritas.lin) && (elementos_mapa->chapeiro.col + 1 == elementos_mapa->fritas.col)){
		push(topo, elementos_mapa->fritas.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->refrigerante.lin) && (elementos_mapa->chapeiro.col + 1 == elementos_mapa->refrigerante.col)){
		push(topo, elementos_mapa->refrigerante.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->lixeira.lin) && (elementos_mapa->chapeiro.col + 1 == elementos_mapa->lixeira.col)){
		uso_lixeira++;
		pop(topo);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->entrega.lin) && (elementos_mapa->chapeiro.col + 1 == elementos_mapa->entrega.col)){
		if (verifica_pedido(topo, comeco) == 1){
				pontos += 10;
		} else {
			pedidos_errados++;
		}

		destroi_refeicao(topo);
		return 1;
	
	} else if (elementos_mapa->chapeiro.col + 1 >= elementos_mapa->parede_lateral.col){  
		return 1; //se for tentar andar para a direita do limite maximo das colunas do mapa, a parede lateral
	}

	return 0;
}

int move_esquerda(struct refeicao* topo, struct refeicao* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais* elementos_mapa){
//verifica se o personagem esta tentando "subir" em uma estacao, se sim, faz o que ela pede e retorna o inteiro 1, se nao retorna 0

	if ((elementos_mapa->chapeiro.lin == elementos_mapa->hamburguer.lin) && (elementos_mapa->chapeiro.col - 1 == elementos_mapa->hamburguer.col)){
		push(topo, elementos_mapa->hamburguer.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->pao_cima.lin) && (elementos_mapa->chapeiro.col - 1 == elementos_mapa->pao_cima.col)){
		push(topo, elementos_mapa->pao_cima.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->pao_baixo.lin) && (elementos_mapa->chapeiro.col - 1 == elementos_mapa->pao_baixo.col)){
		push(topo, elementos_mapa->pao_baixo.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->queijo.lin) && (elementos_mapa->chapeiro.col - 1 == elementos_mapa->queijo.col)){
		push(topo, elementos_mapa->queijo.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->salada.lin) && (elementos_mapa->chapeiro.col - 1 == elementos_mapa->salada.col)){
		push(topo, elementos_mapa->salada.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->fritas.lin) && (elementos_mapa->chapeiro.col - 1 == elementos_mapa->fritas.col)){
		push(topo, elementos_mapa->fritas.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->refrigerante.lin) && (elementos_mapa->chapeiro.col - 1 == elementos_mapa->refrigerante.col)){
		push(topo, elementos_mapa->refrigerante.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->lixeira.lin) && (elementos_mapa->chapeiro.col - 1 == elementos_mapa->lixeira.col)){
		uso_lixeira++;
		pop(topo);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin == elementos_mapa->entrega.lin) && (elementos_mapa->chapeiro.col - 1 == elementos_mapa->entrega.col)){
		if (verifica_pedido(topo, comeco) == 1){
				pontos += 10;
		} else {
			pedidos_errados++;
		}

		destroi_refeicao(topo);
		return 1;
	
	} else if (elementos_mapa->chapeiro.col - 1 <= 0){  
		return 1; //se for tentar andar para a direita do limite maximo das colunas do mapa, a parede lateral que fica na coluna 0
	}

	return 0;
}

int move_baixo(struct refeicao* topo, struct refeicao* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais* elementos_mapa){
//verifica se o personagem esta tentando "subir" em uma estacao, se sim, faz o que ela pede e retorna o inteiro 1, se nao retorna 0

	if ((elementos_mapa->chapeiro.lin + 1 == elementos_mapa->hamburguer.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->hamburguer.col)){
		push(topo, elementos_mapa->hamburguer.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin + 1 == elementos_mapa->pao_cima.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->pao_cima.col)){
		push(topo, elementos_mapa->pao_cima.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin + 1  == elementos_mapa->pao_baixo.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->pao_baixo.col)){
		push(topo, elementos_mapa->pao_baixo.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin + 1 == elementos_mapa->queijo.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->queijo.col)){
		push(topo, elementos_mapa->queijo.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin + 1 == elementos_mapa->salada.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->salada.col)){
		push(topo, elementos_mapa->salada.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin + 1 == elementos_mapa->fritas.lin) && (elementos_mapa->chapeiro.col = elementos_mapa->fritas.col)){
		push(topo, elementos_mapa->fritas.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin + 1 == elementos_mapa->refrigerante.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->refrigerante.col)){
		push(topo, elementos_mapa->refrigerante.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin + 1 == elementos_mapa->lixeira.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->lixeira.col)){
		uso_lixeira++;
		pop(topo);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin + 1 == elementos_mapa->entrega.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->entrega.col)){
		if (verifica_pedido(topo, comeco) == 1){
				pontos += 10;
		} else {
			pedidos_errados++;
		}

		destroi_refeicao(topo);
		return 1;
	
	} else if (elementos_mapa->chapeiro.lin + 1 >= elementos_mapa->parede_horizontal.lin){  
		return 1; //se for tentar andar para abaixo do limite maximo das linhas do mapa, a parede horizontal
	}

	return 0;
}

int move_cima(struct refeicao* topo, struct refeicao* comeco, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais* elementos_mapa){
//verifica se o personagem esta tentando "subir" em uma estacao, se sim, faz o que ela pede e retorna o inteiro 1, se nao retorna 0

	if ((elementos_mapa->chapeiro.lin - 1 == elementos_mapa->hamburguer.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->hamburguer.col)){
		push(topo, elementos_mapa->hamburguer.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin - 1 == elementos_mapa->pao_cima.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->pao_cima.col)){
		push(topo, elementos_mapa->pao_cima.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin - 1 == elementos_mapa->pao_baixo.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->pao_baixo.col)){
		push(topo, elementos_mapa->pao_baixo.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin - 1 == elementos_mapa->queijo.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->queijo.col)){
		push(topo, elementos_mapa->queijo.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin - 1 == elementos_mapa->salada.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->salada.col)){
		push(topo, elementos_mapa->salada.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin - 1 == elementos_mapa->fritas.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->fritas.col)){
		push(topo, elementos_mapa->fritas.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin - 1 == elementos_mapa->refrigerante.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->refrigerante.col)){
		push(topo, elementos_mapa->refrigerante.ingrediente);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin - 1 == elementos_mapa->lixeira.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->lixeira.col)){
		uso_lixeira++;
		pop(topo);
		return 1;

	} else if ((elementos_mapa->chapeiro.lin - 1 == elementos_mapa->entrega.lin) && (elementos_mapa->chapeiro.col == elementos_mapa->entrega.col)){
		if (verifica_pedido(topo, comeco) == 1){
				pontos += 10;
		} else {
			pedidos_errados++;
		}

		destroi_refeicao(topo);
		return 1;
	
	} else if (elementos_mapa->chapeiro.lin - 1 <= 0){  
		return 1; //se for tentar andar para acima do limite maximo das linhas do mapa, a parede horizontal que fica na coluna 0
	}

	return 0;
}
