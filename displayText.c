#include "displayText.h"
#include "buffer.h"
#include <ncurses.h>

void DisplayText()
{
move(1,0);
if (buffer)
	{
		for( int i=0; i<numLines; i++) 
		{
			for(int j =0; j < sizes[i]; j++)
			mvprintw(i+1, j, "%c", buffer[i][j]);
		}
	}

}
