#include "modes.h"
#include <ncurses.h>

void changeMode(char* string){
	getyx(stdscr, r, c);
	move(LINES-1, 0);
	clrtoeol();
	printw("%s", string);
	move(r, c);
}
