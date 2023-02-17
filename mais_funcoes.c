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

//criar funcao de imprimir mapa, de inicializar os elementos do mapa, de game over, animacao inicial. determinar o numero max de clientes.

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
	elementos_mapa->hamburguer.simbolo[1] = 'H';
	elementos_mapa->hamburguer.simbolo[3] = ']';
}
//planejamento: inicializa tudo, case switch para mover. checa se encostou em algo, checa os contadores para ver se eh game over.
