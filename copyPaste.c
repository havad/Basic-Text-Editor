#include "copyPaste.h"
#include "buffer.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void CopyPaste (char method)
{
	getyx(stdscr, r, c);
	noecho();
	if(method == 'c')
	{
		if(r < numLines + 1){
			clipboard = buffer[r-1];
			SizeOfString = sizes[r-1]-1;
		}
	}

	if(method == 'p')
	{
		if(r < numLines + 1){
			UpdateBuffer(2, r-1, 0, "\n", 0);
			UpdateBuffer(3, r-1, 0, clipboard, SizeOfString);
			insertln();
			char* temp = malloc(SizeOfString*sizeof(char));
			for(int i = 0; i < SizeOfString; i++)
				temp[i] = clipboard[i];
			move(r, 0);
			clrtoeol();
			mvinsstr(r, 0, temp);
		} 
	}

}
