#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "de-burguer.h"


int main(){
	int pontos, erros = 0; 
	struct locais *elementos_mapa;

	inicializa_ncurses();
	int movimento = getch();

	switch (movimento){
		case KEY_RIGHT:{
			if (move_direita(topo, comeco, &pontos, &erros, elementos_mapa) == 0)
				mvaddch(elementos_mapa->chapeiro.lin, elementos_mapa->chapeiro.col, elementos_mapa->chapeiro.simbolo);
		} break;


	}

	endwin();
	return 0;
}