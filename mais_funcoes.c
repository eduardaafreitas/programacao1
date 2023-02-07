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

//criar funcao de imprimir mapa, de inicializar os elementos do mapa, de game over, animacao inicial, e adaptar as de movimento

void regras(){
    char a;
    a = '.';
    while (a != ' '){
        printw("Bem vindo ao jogo De-Burguer!\n");
	//completar
    }
}

void pontuacao(int pontos){
    //escolher onde vai ficar e as cores (declara elas com attron)
    printw("PONTOS: %d", pontos);
}

//planejamento: inicializa tudo, case switch para mover. checa se encostou em algo, checa os contadores para ver se eh game over.