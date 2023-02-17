#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "de-burguer.h"


int main(){
	int pontos, pedidos_errados, uso_lixeira, num_clientes, num_pedidos_certos = 0; 
	struct locais *elementos_mapa;
	struct refeicao* topo = NULL;
	struct pedido* comeco = NULL;
	struct pedido* fim = NULL;
	inicializa_fila(comeco, fim, &num_clientes);
	inicializa_ncurses();
	int movimento = getch();

	while (num_pedidos_certos < 8){
		switch (movimento){
			case KEY_RIGHT:{
				if (move_direita(topo, comeco, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0)
					mvaddch(elementos_mapa->chapeiro.lin, elementos_mapa->chapeiro.col + 1, elementos_mapa->chapeiro.simbolo);
			} break;
	
			case KEY_LEFT:{
				if (move_esquerda(topo, comeco, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0)
					mvaddch(elementos_mapa->chapeiro.lin, elementos_mapa->chapeiro.col - 1, elementos_mapa->chapeiro.simbolo);
			} break;
	
			case KEY_DOWN:{
				if (move_baixo(topo, comeco, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0)
					mvaddch(elementos_mapa->chapeiro.lin + 1, elementos_mapa->chapeiro.col, elementos_mapa->chapeiro.simbolo);
			} break;
	
			case KEY_UP:{
				if (move_cima(topo, comeco, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0)
					mvaddch(elementos_mapa->chapeiro.lin - 1, elementos_mapa->chapeiro.col, elementos_mapa->chapeiro.simbolo);
			} break;
		}
		
		if ((num_clientes < 7) && (rand()%2 == 1)){
				insere_fim(comeco, fim, &num_clientes);
				num_clientes++;
			}
		
		movimento = getch();
	}
	endwin();
	return 0;
}
