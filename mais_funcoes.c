#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "de-burguer.h"

//esse arquivo possui as funcoes que ainda estao sendo escritas!

// animacao inicial. ok

//regras ok

// gameover em dev

void game_over(){
    clear();
    mvprintw(0, 14, "GAME OVER");
    mvprintw(1, 14, "Pressione qualquer tecla para sair");
    getch();
    endwin();
    exit(0);
}