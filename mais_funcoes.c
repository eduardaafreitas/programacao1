#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "de-burguer.h"

//esse arquivo possui as funoces que ainda estao sendo escritas!

// animacao inicial.



t_queue *verificaPedido(t_queue *clientes, t_pilha *burger, int *vidas, int *pontos) {

    t_queue *aux, *cliente;
    t_pilha *auxb;
  
    char icli, ibur;
    int flag=0;

    auxb = burger;
    aux = clientes;
    cliente = aux;

    FILE *p;
    p = fopen("teste.txt", "a");

    // testar o tamanho0
    if(auxb->topo != cliente->burg->topo){
        flag=1;
    }else{
        // testar os ingredientes
        for (int i = burger->topo; i >= 0; i--) {
            pop(cliente->burg, &icli);
            pop(auxb, &ibur);
            if(icli!=ibur){
                flag = 1;
                
            }
            fprintf(p, "[%c] [%c]\n", ibur,icli);
        }
    }
    
    if(flag == 1){
        (*vidas)--;
        mvprintw (13, 3, "VIDAS: %d", *vidas);
        clientes = dequeue(aux);
        destroiRefeicao(burger);
    } else {
        clientes = dequeue(aux);
        *pontos = *pontos + 100;
    }

    fclose(p);
    return clientes;
}

void inicializa_ncurses(){
    initscr();            //inicializa a tela
    raw();                //desabilita o buffer
    noecho();             //nao mostra os caracteres digitados
    curs_set(FALSE);      //não mostra o cursor na tela 
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

