#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "de-burguer.h"

//esse arquivo possui as funcoes que ainda estao sendo escritas!

// animacao inicial.


void regras(){
    char a;
    a = '.';
    while (a != ' '){
        printw("Bem vindo ao jogo De-Burguer!\n");
        printw("-> O objetivo do jogo eh fazer o maior numero de pedidos possivel sem errar.\n");
        printw("-> Para isso, voce deve usar as setas do teclado para se movimentar e coletar os ingredientes.\n");
        printw("-> Cada pedido vale 10 pontos, sendo 8 pedidos o maximo.\n");
        printw("-> Voce pode errar 3 pedidos e usar a lixeira 5 vezes.\n");
        printw("-> Aperte espaco para continuar.\n");
        printw("-> Aperte f1 para sair.\n");
        a = getch();
    }
}

void game_over(){
	
}