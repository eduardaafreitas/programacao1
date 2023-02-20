#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "de-burguer.h"

void inicializa_ncurses(){
    initscr();            //inicializa a tela
	//verifica_cores();	  //verifica se o terminal suporta cores
    raw();                //desabilita o buffer
    noecho();             //nao mostra os caracteres digitados
    curs_set(FALSE);      //não mostra o cursor na tela 
    keypad(stdscr, TRUE); //habilita leitura de setas 
    //cores??
	start_color();		  //habilita cores
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

int *verifica_pedido(struct pilha* refeicao, struct fila_clientes* fila){
    int num_cardapio;
    int flag = 0;
    num_cardapio = fila->comeco->num_refeicao;

	char* cardapio[] = { //define as refeicoes que serao util para checar o lanche e imprimi-lo na tela 
		[X_Burguer] = "pHQP",
		[X_Salada] = "pHSP",
		[Combo_1] = "pHQPFR",
		[Combo_2] = "pHSPFR",
		[Vegetariano] = "pQPFR",
		[Vegano] = "SFR"
	};

    for (int i = 0; i < strlen(cardapio[num_cardapio]); i++){
        if (refeicao->topo->ingrediente != cardapio[num_cardapio]){
            flag = 1;
        }
    }

}

struct pedido* cria_pedido(int* num_clientes){
	struct pedido* novo = malloc(sizeof(struct pedido));
	novo->prox = NULL;
	novo->anterior = NULL;
	novo->cliente = (*num_clientes++);
	novo->num_refeicao = rand()%6;

	return novo;
}

int fila_vazia(struct fila_clientes* fila){
	//verifica se a fila etsa vazia

	if ((fila->comeco == NULL) && (fila->fim == NULL)){
		return 1;
	}
	return 0;
}

void insere_fim(struct fila_clientes* fila, int* num_clientes){
	struct pedido* novo = cria_pedido(num_clientes);

	if (fila_vazia(fila) == 1){
		fila->comeco = novo;
		fila->fim = novo;
	} else {
		//adiciona o novo cliente e atualiza o ponteiro para o fim
		novo->anterior = fila->fim;
		fila->fim->prox = novo;
		fila->fim = novo;
	}
}

struct fila_clientes* inicializa_fila(int* num_clientes){
	//começa o jogo com tres pedidos ja na fila
	struct fila_clientes* fila;
	fila = malloc(sizeof(struct fila_clientes));
	fila->comeco = NULL;
	fila->fim = NULL;

	insere_fim(fila, num_clientes);
	insere_fim(fila, num_clientes);
	insere_fim(fila, num_clientes);

	return fila;
}

void retira_comeco(struct fila_clientes* fila){
	struct pedido* aux = fila->comeco;

	fila->comeco = aux->prox;
	aux->prox->anterior = NULL;
	aux->prox = NULL;

	free(aux);
}

struct pilha* inicializa_pilha(){
	struct pilha* refeicao;
	refeicao = malloc(sizeof(struct pilha));
	refeicao->topo = NULL;

	return refeicao;
}

void push(struct pilha* refeicao, char ingrediente){
	struct ingredientes* novo = malloc(sizeof(struct ingredientes));
	novo->ingrediente = ingrediente;

	if (refeicao->topo == NULL){
		novo->anterior = NULL;
		refeicao->topo = novo;
	} else {
		novo->anterior = refeicao->topo;
		refeicao->topo = novo;
	}
}

void pop(struct pilha* refeicao){
	struct ingredientes* aux = refeicao->topo;

	refeicao->topo = aux->anterior;
	free(aux);
}

void destroi_refeicao(struct pilha* refeicao){
	while (refeicao->topo != NULL)
		pop(refeicao);
}

void imprime_refeicao(struct pilha* refeicao){
	struct ingredientes* aux = refeicao->topo;
	int i = 1;

	mvprintw(0, 28, "Seu preparo atual:");
	while (aux != NULL){
		mvprintw(i, 32, "[%c] ", aux->ingrediente);
		i++;
		aux = aux->anterior;
	}

	free(aux);
}


int verifica_direita(struct pilha* refeicao, struct fila_clientes* fila, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa){
//verifica se o personagem esta tentando "subir" em uma estacao, se sim, faz o que ela pede e retorna o inteiro 1, se nao retorna 0

	if ((elementos_mapa.chapeiro.lin == elementos_mapa.hamburguer.lin) && ((elementos_mapa.chapeiro.col + 1 == elementos_mapa.hamburguer.col[0]) 
			|| (elementos_mapa.chapeiro.col + 1 == elementos_mapa.hamburguer.col[1]) || (elementos_mapa.chapeiro.col + 1 == elementos_mapa.hamburguer.col[2]))){

		push(refeicao, elementos_mapa.hamburguer.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.pao_cima.lin) && ((elementos_mapa.chapeiro.col + 1 == elementos_mapa.pao_cima.col[0]) 
			|| (elementos_mapa.chapeiro.col + 1 == elementos_mapa.pao_cima.col[1]) || (elementos_mapa.chapeiro.col + 1 == elementos_mapa.pao_cima.col[2]))){

		push(refeicao, elementos_mapa.pao_cima.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.pao_baixo.lin) && ((elementos_mapa.chapeiro.col + 1 == elementos_mapa.pao_baixo.col[0]) 
			|| (elementos_mapa.chapeiro.col + 1 == elementos_mapa.pao_baixo.col[1]) || (elementos_mapa.chapeiro.col + 1 == elementos_mapa.pao_baixo.col[2]))){

		push(refeicao, elementos_mapa.pao_baixo.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.queijo.lin) && ((elementos_mapa.chapeiro.col + 1 == elementos_mapa.queijo.col[0]) 
			|| (elementos_mapa.chapeiro.col + 1 == elementos_mapa.queijo.col[1]) || (elementos_mapa.chapeiro.col + 1 == elementos_mapa.queijo.col[2]))){

		push(refeicao, elementos_mapa.queijo.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.salada.lin) && ((elementos_mapa.chapeiro.col + 1 == elementos_mapa.salada.col[0]) 
			|| (elementos_mapa.chapeiro.col + 1 == elementos_mapa.salada.col[1]) || (elementos_mapa.chapeiro.col + 1 == elementos_mapa.salada.col[2]))){

		push(refeicao, elementos_mapa.salada.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.fritas.lin) && ((elementos_mapa.chapeiro.col + 1 == elementos_mapa.fritas.col[0]) 
			|| (elementos_mapa.chapeiro.col + 1 == elementos_mapa.fritas.col[1]) || (elementos_mapa.chapeiro.col + 1 == elementos_mapa.fritas.col[2]))){

		push(refeicao, elementos_mapa.fritas.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.refrigerante.lin) && ((elementos_mapa.chapeiro.col + 1 == elementos_mapa.refrigerante.col[0]) 
			|| (elementos_mapa.chapeiro.col + 1 == elementos_mapa.refrigerante.col[1]) || (elementos_mapa.chapeiro.col + 1 == elementos_mapa.refrigerante.col[2]))){
		push(refeicao, elementos_mapa.refrigerante.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.lixeira.lin) && (elementos_mapa.chapeiro.col + 1 == elementos_mapa.lixeira.col)){
		uso_lixeira++;
		destroi_refeicao(refeicao);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.entrega.lin) && (elementos_mapa.chapeiro.col + 1 == elementos_mapa.entrega.col)){
		if (*verifica_pedido(refeicao, fila) == 1){
				(*pontos) += 10;
		} else {
			(*pedidos_errados)++;
		}

		destroi_refeicao(refeicao);
		return 1;
	
	} else if (elementos_mapa.chapeiro.col + 1 >= elementos_mapa.parede_direita.col){  
		return 1; //se for tentar andar para a direita do limite maximo das colunas do mapa, a parede lateral
	}

	return 0;
}

int verifica_esquerda(struct pilha* refeicao, struct fila_clientes* fila, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa){
//verifica se o personagem esta tentando "subir" em uma estacao, se sim, faz o que ela pede e retorna o inteiro 1, se nao retorna 0

	if ((elementos_mapa.chapeiro.lin == elementos_mapa.hamburguer.lin) && ((elementos_mapa.chapeiro.col - 1 == elementos_mapa.hamburguer.col[0]) 
			|| (elementos_mapa.chapeiro.col - 1 == elementos_mapa.hamburguer.col[1]) || (elementos_mapa.chapeiro.col - 1 == elementos_mapa.hamburguer.col[2]))){

		push(refeicao, elementos_mapa.hamburguer.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.pao_cima.lin) && ((elementos_mapa.chapeiro.col - 1 == elementos_mapa.pao_cima.col[0]) 
			|| (elementos_mapa.chapeiro.col - 1 == elementos_mapa.pao_cima.col[1]) || (elementos_mapa.chapeiro.col - 1 == elementos_mapa.pao_cima.col[2]))){

		push(refeicao, elementos_mapa.pao_cima.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.pao_baixo.lin) && ((elementos_mapa.chapeiro.col - 1 == elementos_mapa.pao_baixo.col[0]) 
			|| (elementos_mapa.chapeiro.col - 1 == elementos_mapa.pao_baixo.col[1]) || (elementos_mapa.chapeiro.col - 1 == elementos_mapa.pao_baixo.col[2]))){

		push(refeicao, elementos_mapa.pao_baixo.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.queijo.lin) && ((elementos_mapa.chapeiro.col - 1 == elementos_mapa.queijo.col[0]) 
			|| (elementos_mapa.chapeiro.col - 1 == elementos_mapa.queijo.col[1]) || (elementos_mapa.chapeiro.col - 1 == elementos_mapa.queijo.col[2]))){

		push(refeicao, elementos_mapa.queijo.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.salada.lin) && ((elementos_mapa.chapeiro.col - 1 == elementos_mapa.salada.col[0]) 
			|| (elementos_mapa.chapeiro.col - 1 == elementos_mapa.salada.col[1]) || (elementos_mapa.chapeiro.col - 1 == elementos_mapa.salada.col[2]))){

		push(refeicao, elementos_mapa.salada.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.fritas.lin) && ((elementos_mapa.chapeiro.col - 1 == elementos_mapa.fritas.col[0]) 
			|| (elementos_mapa.chapeiro.col - 1 == elementos_mapa.fritas.col[1]) || (elementos_mapa.chapeiro.col - 1 == elementos_mapa.fritas.col[2]))){

		push(refeicao, elementos_mapa.fritas.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.refrigerante.lin) && ((elementos_mapa.chapeiro.col - 1 == elementos_mapa.refrigerante.col[0]) 
			|| (elementos_mapa.chapeiro.col - 1 == elementos_mapa.refrigerante.col[1]) || (elementos_mapa.chapeiro.col - 1 == elementos_mapa.refrigerante.col[2]))){

		push(refeicao, elementos_mapa.refrigerante.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.lixeira.lin) && (elementos_mapa.chapeiro.col - 1 == elementos_mapa.lixeira.col)){
		uso_lixeira++;
		destroi_refeicao(refeicao);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin == elementos_mapa.entrega.lin) && (elementos_mapa.chapeiro.col - 1 == elementos_mapa.entrega.col)){
		if (*verifica_pedido(refeicao, fila) == 1){
				(*pontos) += 10;
		} else {
			(*pedidos_errados)++;
		}

		destroi_refeicao(refeicao);
		return 1;
	
	} else if (elementos_mapa.chapeiro.col - 1 <= 0){  
		return 1; //se for tentar andar para a direita do limite maximo das colunas do mapa, a parede lateral que fica na coluna 0
	}

	return 0;
}

int verifica_baixo(struct pilha* refeicao, struct fila_clientes* fila, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa){
//verifica se o personagem esta tentando "subir" em uma estacao, se sim, faz o que ela pede e retorna o inteiro 1, se nao retorna 0

	if ((elementos_mapa.chapeiro.lin + 1 == elementos_mapa.hamburguer.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.hamburguer.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.hamburguer.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.hamburguer.col[2]))){

		push(refeicao, elementos_mapa.hamburguer.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin + 1 == elementos_mapa.pao_cima.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.pao_cima.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.pao_cima.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.pao_cima.col[2]))){

		push(refeicao, elementos_mapa.pao_cima.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin + 1  == elementos_mapa.pao_baixo.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.pao_baixo.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.pao_baixo.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.pao_baixo.col[2]))){
		push(refeicao, elementos_mapa.pao_baixo.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin + 1 == elementos_mapa.queijo.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.queijo.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.queijo.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.queijo.col[2]))){

		push(refeicao, elementos_mapa.queijo.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin + 1 == elementos_mapa.salada.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.salada.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.salada.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.salada.col[2]))){

		push(refeicao, elementos_mapa.salada.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin + 1 == elementos_mapa.fritas.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.fritas.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.fritas.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.fritas.col[2]))){

		push(refeicao, elementos_mapa.fritas.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin + 1 == elementos_mapa.refrigerante.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.refrigerante.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.refrigerante.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.refrigerante.col[2]))){

		push(refeicao, elementos_mapa.refrigerante.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin + 1 == elementos_mapa.lixeira.lin) && (elementos_mapa.chapeiro.col == elementos_mapa.lixeira.col)){
		uso_lixeira++;
		destroi_refeicao(refeicao);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin + 1 == elementos_mapa.entrega.lin) && (elementos_mapa.chapeiro.col == elementos_mapa.entrega.col)){
		if (*verifica_pedido(refeicao, fila) == 1){
				(*pontos) += 10;
		} else {
			(*pedidos_errados)++;
		}

		destroi_refeicao(refeicao);
		return 1;
	
	} else if (elementos_mapa.chapeiro.lin + 1 >= elementos_mapa.parede_baixo.lin){  
		return 1; //se for tentar andar para abaixo do limite maximo das linhas do mapa, a parede horizontal
	}

	return 0;
}

int verifica_cima(struct pilha* refeicao, struct fila_clientes* fila, int* pontos, int* pedidos_errados, int* uso_lixeira, struct locais elementos_mapa){
//verifica se o personagem esta tentando "subir" em uma estacao, se sim, faz o que ela pede e retorna o inteiro 1, se nao retorna 0

	if ((elementos_mapa.chapeiro.lin - 1 == elementos_mapa.hamburguer.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.hamburguer.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.hamburguer.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.hamburguer.col[2]))){

		push(refeicao, elementos_mapa.hamburguer.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin - 1 == elementos_mapa.pao_cima.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.pao_cima.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.pao_cima.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.pao_cima.col[2]))){

		push(refeicao, elementos_mapa.pao_cima.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin - 1 == elementos_mapa.pao_baixo.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.pao_baixo.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.pao_baixo.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.pao_baixo.col[2]))){

		push(refeicao, elementos_mapa.pao_baixo.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin - 1 == elementos_mapa.queijo.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.queijo.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.queijo.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.queijo.col[2]))){

		push(refeicao, elementos_mapa.queijo.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin - 1 == elementos_mapa.salada.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.salada.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.salada.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.salada.col[2]))){

		push(refeicao, elementos_mapa.salada.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin - 1 == elementos_mapa.fritas.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.fritas.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.fritas.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.fritas.col[2]))){

		push(refeicao, elementos_mapa.fritas.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin - 1 == elementos_mapa.refrigerante.lin) && ((elementos_mapa.chapeiro.col == elementos_mapa.refrigerante.col[0]) 
			|| (elementos_mapa.chapeiro.col == elementos_mapa.refrigerante.col[1]) || (elementos_mapa.chapeiro.col == elementos_mapa.refrigerante.col[2]))){

		push(refeicao, elementos_mapa.refrigerante.ingrediente);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin - 1 == elementos_mapa.lixeira.lin) && (elementos_mapa.chapeiro.col == elementos_mapa.lixeira.col)){
		uso_lixeira++;
		destroi_refeicao(refeicao);
		return 1;

	} else if ((elementos_mapa.chapeiro.lin - 1 == elementos_mapa.entrega.lin) && (elementos_mapa.chapeiro.col == elementos_mapa.entrega.col)){
		if (*verifica_pedido(refeicao, fila) == 1){
				(*pontos) += 10;
		} else {
			(*pedidos_errados)++;
		}

		destroi_refeicao(refeicao);
		return 1;
	
	} else if ((elementos_mapa.chapeiro.lin - 1 <= 0) && (elementos_mapa.chapeiro.col != elementos_mapa.entrega.col)){  
		return 1; //se for tentar andar para acima do limite maximo das linhas do mapa, a parede horizontal que fica na linha 0
	}

	return 0;
}

void inicializa_elem_mapa(struct locais* elementos_mapa){

	//lixeira
	elementos_mapa->lixeira.simbolo = 'o';
	elementos_mapa->lixeira.lin = 5;
	elementos_mapa->lixeira.col = 25;

	//ponto de entrega
	elementos_mapa->entrega.simbolo = '@';
	elementos_mapa->entrega.lin = 0;
	elementos_mapa->entrega.col = 13;

	//chapeiro
	elementos_mapa->chapeiro.simbolo = '&';
	elementos_mapa->chapeiro.lin = 2;
	elementos_mapa->chapeiro.col = 23;

	//hamburguer
	elementos_mapa->hamburguer.simbolo[0] = '[';
	elementos_mapa->hamburguer.simbolo[1] =  'H';
	elementos_mapa->hamburguer.simbolo[2] = ']';
	elementos_mapa->hamburguer.lin = 7;
	elementos_mapa->hamburguer.col[0] = 7;
	elementos_mapa->hamburguer.col[1] = 8;
	elementos_mapa->hamburguer.col[2] = 9;
	elementos_mapa->hamburguer.ingrediente = 'H';

	//fritas
	elementos_mapa->fritas.simbolo[0] = '[';
	elementos_mapa->fritas.simbolo[1] = 'F';
	elementos_mapa->fritas.simbolo[2] = '[';
	elementos_mapa->fritas.lin = 4;
	elementos_mapa->fritas.col[0] = 2;
	elementos_mapa->fritas.col[1] = 3;
	elementos_mapa->fritas.col[2] = 4;
	elementos_mapa->fritas.ingrediente = 'F';

	//pao cima
	elementos_mapa->pao_cima.simbolo[0] = '[';
	elementos_mapa->pao_cima.simbolo[1] = 'P';
	elementos_mapa->pao_cima.simbolo[2] = '[';
	elementos_mapa->pao_cima.lin = 7;
	elementos_mapa->pao_cima.col[0] = 22;
	elementos_mapa->pao_cima.col[1] = 23;
	elementos_mapa->pao_cima.col[2] = 24;
	elementos_mapa->pao_cima.ingrediente = 'P';

	//pao baixo
	elementos_mapa->pao_baixo.simbolo[0] = '[';
	elementos_mapa->pao_baixo.simbolo[1] = 'p';
	elementos_mapa->pao_baixo.simbolo[2] = '[';
	elementos_mapa->pao_baixo.lin = 7;
	elementos_mapa->pao_baixo.col[0] = 2;
	elementos_mapa->pao_baixo.col[1] = 3;
	elementos_mapa->pao_baixo.col[2] = 4;
	elementos_mapa->pao_baixo.ingrediente = 'p';

	//queijo
	elementos_mapa->queijo.simbolo[0] = '[';
	elementos_mapa->queijo.simbolo[1] = 'Q';
	elementos_mapa->queijo.simbolo[2] = '[';
	elementos_mapa->queijo.lin = 7;
	elementos_mapa->queijo.col[0] = 12;
	elementos_mapa->queijo.col[1] = 13;
	elementos_mapa->queijo.col[2] = 14;
	elementos_mapa->queijo.ingrediente = 'Q';

	//salada
	elementos_mapa->salada.simbolo[0] = '[';
	elementos_mapa->salada.simbolo[1] = 'S';
	elementos_mapa->salada.simbolo[2] = '[';
	elementos_mapa->salada.lin = 7;
	elementos_mapa->salada.col[0] = 17;
	elementos_mapa->salada.col[1] = 18;
	elementos_mapa->salada.col[2] = 19;
	elementos_mapa->salada.ingrediente = 'S';

	//refrigerante
	elementos_mapa->refrigerante.simbolo[0] = '[';
	elementos_mapa->refrigerante.simbolo[1] = 'R';
	elementos_mapa->refrigerante.simbolo[2] = '[';
	elementos_mapa->refrigerante.lin = 2;
	elementos_mapa->refrigerante.col[0] = 2;
	elementos_mapa->refrigerante.col[1] = 3;
	elementos_mapa->refrigerante.col[2] = 4;
	elementos_mapa->refrigerante.ingrediente = 'R';

	//paredes 
	elementos_mapa->parede_direita.col = 26;
	elementos_mapa->parede_direita.simbolo = '|';

	elementos_mapa->parede_baixo.lin = 8;
	elementos_mapa->parede_baixo.simbolo = '-';
}

void pontuacao(int* pontos){
    mvprintw(10, 0, "PONTOS: %d", (*pontos));
}

void imprime_tela(struct locais* elementos_mapa, struct pilha* refeicao, int* pontos){
	//limpa tela
	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 50; j++){
			mvprintw(i, j, " ");
		}
	}

	imprime_refeicao(refeicao);
	pontuacao(pontos);

	int i;
	//imprime parede esquerda
	for (i = 0; i <= 8; i++){
		mvprintw(i, 0, "|");
	}

	//imprime parede direita
	for (i = 0; i <= 8; i++){
		mvprintw(i, 26, "|");
	}

	//imprime parede baixo
	for (i = 0; i <= 26; i++){
		mvprintw(8, i, "-");
	}

	//imprime parede cima
	for (i = 0; i <= 26; i++){
		mvprintw(0, i, "-");
	}

	//elementos do mapa
	mvprintw(5, 25, "o");
	mvprintw(0, 13, "@");
	mvprintw(elementos_mapa->chapeiro.lin, elementos_mapa->chapeiro.col, "&");
	mvprintw(7, 7, "[H]");
	mvprintw(4, 2, "[F]");
	mvprintw(7, 22, "[P]");
	mvprintw(7, 2, "[p]");
	mvprintw(7, 12, "[Q]");
	mvprintw(7, 17, "[S]");
	mvprintw(2, 2, "[R]");
	refresh();
}