#include "printTitle.h"
#include <ncurses.h>

void printTitle(char *filename){
	attron(A_BOLD);										//Makes the text bold
	attron(A_UNDERLINE);							//Underlines the text
	mvprintw(0, 0, "Filename: %s		Group: 9 ", filename);   //Prints the title bar
	clrtoeol();												
	attroff(A_BOLD);									//Unbolds the text
	attroff(A_UNDERLINE);							//Un-underline the text
}
