#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "de-burguer.h"

//esse arquivo possui as funoces que ainda estao sendo escritas!

// animacao inicial.


void inicializa_ncurses(){
    initscr();            //inicializa a tela
    raw();                //desabilita o buffer
    noecho();             //nao mostra os caracteres digitados
    curs_set(FALSE);      //no mostra o cursor na tela 
    keypad(stdscr, TRUE); //habilita leitura de setas 
    //cores??
}

void regras(){
    char a;
    a = '.';
    while (a != ' '){
        printw("Bem vindo ao jogo De-Burguer!\n");
	//completar
    }
}

void pontuacao(int* pontos){
    //escolher onde vai ficar e as cores (declara elas com attron)
    printw("PONTOS: %d", (*pontos));
}

void game_over(){
	
}

int imprime_pedidos(struct pedido* comeco){ //imprime os cinco primeiros pedidos da fila
	struct pedido* aux = comeco;

	for (int i = 1; i < 6; i++){
		printf("Pedido %d:\n", i);	//colocar posicao 
		for (int j = 0; j < strlen(cardapio[aux->num_refeicao]); j++){
				printf("[%c] ", cardapio[aux->num_refeicao][j]);
		}
		printf("\n\n");
		aux = aux->prox;
	}
}

void escreve_pilha(struct refeicao* topo){
	struct refeicao* aux = topo;

	while (aux != NULL){
		printf("%d ", aux->ingrediente);

		aux = aux->anterior;
	}
}