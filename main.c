#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "de-burguer.h"

int main(){
	int pontos = 0, pedidos_errados = 0, uso_lixeira = 0, num_clientes = 0; 
	struct locais elementos_mapa;
	struct pilha* refeicao = inicializa_pilha();
	struct fila_clientes* fila = inicializa_fila(&num_clientes);
	inicializa_elem_mapa(&elementos_mapa);
	imprime_tela(&elementos_mapa, refeicao, &pontos);
	inicializa_ncurses();
	int movimento = getch();

	while (pontos <= 80){ //cada pedido vale 10 pontos, sendo 8 pedidos (num_clientes) o maximo
		switch (movimento){
			case KEY_RIGHT:{
				if (verifica_direita(refeicao, fila, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0){
					elementos_mapa.chapeiro.col++;
				}
			} break;
	
			case KEY_LEFT:{
				if (verifica_esquerda(refeicao, fila, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0){
					elementos_mapa.chapeiro.col--;
				}
			} break;
	
			case KEY_DOWN:{
				if (verifica_baixo(refeicao, fila, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0){
					elementos_mapa.chapeiro.lin++;
				}
			} break;
	
			case KEY_UP:{
				if (verifica_cima(refeicao, fila, &pontos, &pedidos_errados, &uso_lixeira, elementos_mapa) == 0){
					elementos_mapa.chapeiro.lin--;
				}
			} break;
		}
		imprime_tela(&elementos_mapa, refeicao, &pontos);

		if ((pedidos_errados == 3) || (uso_lixeira == 5)){ //checa se eh game over
				//game_over();
		}
		
		if ((num_clientes < 8) && (rand()%2 == 1)){	//randomiza quando um novo cliente chegará 
				insere_fim(fila, &num_clientes);
				num_clientes++;
		}
		movimento = getch();
	}
	endwin();
	return 0;
}
