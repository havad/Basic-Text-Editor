#include "deleteLine.h"
#include "buffer.h"
#include <ncurses.h>

void deleteLine(){ 
  cbreak();      
  noecho();      
  keypad(stdscr, TRUE);    
  getyx(stdscr, y, x); // get current curser position
  if(y < numLines){
    move(y, 0);     // move to begining of line
    UpdateBuffer(1, y-1, 0, NULL, 0);
    deleteln();     // Deletes line and move text up
    getyx(stdscr, y, x);
	move(LINES-2, 0);
	clrtoeol();
	move(y, x);
  }
}
