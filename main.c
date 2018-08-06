#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <ncurses.h>
#include "buffer.h"                   
#include "commandMode.h"
#include "displayText.h"
#include "printTitle.h"
			
int main(int argc, char* argv[])
{
    char * file = argv[1];	
    if(argc != 2)
    {
	printf("Must enter only one txt file argument. \nUsage: ./main file.txt\n"); 
	return 1;				// checks for proper usage
    }
    if(strstr(file, ".txt") == NULL)
    {
	printf("%s has to be a .txt file. \nUsage: ./main file.txt\n", argv[1]);
	return 1;
    }

    initscr();    	               //Initializes the terminal in curse mode		
    FillBuffer(file);			// calls fill buffer function
    printTitle(file);
    DisplayText();

    refresh();                                //Print file contents on to the real screen
    CommandMode(file);
    FreeBuffer();

    endwin();                                 //Ends the curses mode
    return 0;
}


