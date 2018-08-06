#include "insertLine.h"
#include "buffer.h"
#include <ncurses.h>

void insertLine(){ 
    cbreak();           
    noecho();           
    keypad(stdscr, TRUE);       
    getyx(stdscr, y, x); // get current curser position
    UpdateBuffer(2, y-1, 0, "\n", 0);
    insertln();          // inserts line and move text down
}
