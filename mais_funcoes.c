#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void inicializa_ncurses(){
    initscr();            //inicializa a tela
    raw();                //desabilita o buffer
    noecho();             //nao mostra os caracteres digitados
    curs_set(FALSE);      //no mostra o cursor na tela 
    keypad(stdscr, TRUE); //habilita leitura de setas 
    //cores??
}

//criar funcao de imprimir mapa, de inicializar o chapeiro, de game over, animacao inicial.

void regras(){
    char a;
    a = '.';
    while (a != ' '){
        printw("Bem vindo ao jogo De-Burguer!\n");
    }
}

void pontuacao(int pontos){
    //escolher onde vai ficar e as cores (delcara elas com attron)
    printw("PONTOS: %d", pontos);
}

//planejamento: inicializa tudo, case switch para mover. checa se encostou em algo, checa os contadores para ver se eh game over.