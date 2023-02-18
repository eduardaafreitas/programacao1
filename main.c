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
				if (verifica_direita(topo, comeco, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0)
					mvaddch(elementos_mapa->chapeiro.lin, elementos_mapa->chapeiro.col + 1, elementos_mapa->chapeiro.simbolo);
			} break;
	
			case KEY_LEFT:{
				if (verifica_esquerda(topo, comeco, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0)
					mvaddch(elementos_mapa->chapeiro.lin, elementos_mapa->chapeiro.col - 1, elementos_mapa->chapeiro.simbolo);
			} break;
	
			case KEY_DOWN:{
				if (verifica_baixo(topo, comeco, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0)
					mvaddch(elementos_mapa->chapeiro.lin + 1, elementos_mapa->chapeiro.col, elementos_mapa->chapeiro.simbolo);
			} break;
	
			case KEY_UP:{
				if (verifica_cima(topo, comeco, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0)
					mvaddch(elementos_mapa->chapeiro.lin - 1, elementos_mapa->chapeiro.col, elementos_mapa->chapeiro.simbolo);
			} break;
		}
		
		if ((pedidos_errados == 3) || (uso_lixeira == 5)){
				game_over();
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
