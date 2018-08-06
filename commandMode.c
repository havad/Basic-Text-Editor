#include "commandMode.h"
#include "buffer.h"
#include "editMode.h"
#include "deleteLine.h"
#include "modes.h"
#include "insertLine.h"
#include "save.h"
#include "copyPaste.h"
#include "searchAndReplace.h"
#include <ncurses.h>

void CommandMode(char* file)
{
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	while(1)	//loop until we quit
	{
		changeMode("Command Mode");
		ch = getch();
		if (ch == 113)		//keycode for q to quit
		{
			changeMode("Are you sure you want to quit? Press y to quit, any other key to continue.");//was printw function before changeMode
			ch = getch();
			if (ch == 121 || ch == 89)	//if y or Y, exits
			{
				//return ch;
				break;			
			}
			refresh();	
		}
		else if (ch == 101)
		{
			changeMode("Editing");
			getyx(stdscr, r, c);
			if(r == numLines + 1)
				EditMode(r-1, c);
			else
				EditMode(r, c);
		}
		else if (ch == 115)		//keycode for s to save
		{
			Save(file);
			changeMode("File saved, press any key to continue");
			getch();
			changeMode("Command Mode");
			//return ch;
		}

		else if (ch == 105)		//keycode for i to insert
		{
			insertLine();
			//return ch;		
		}

		else if (ch == 100)		//keycode for d to delete
		{
			deleteLine();
			//delete();
			//return ch;
		}

		else if (ch == 99)		//keycode for c to copy and paste		
		{
			getyx(stdscr, r, c);
			if(r < numLines + 1);
			CopyPaste ('c');
		}
		
		else if (ch == 114)		//keycode for r to search and replace
		{	
			searchAndReplace();
			//return ch;
		}
		
		else if (ch == 112)		//keycode for p to paste to console
		{
			CopyPaste ('p');
		}
		if (ch == KEY_UP)		// checking for special keys
	{
		getyx(stdscr, r, c);		// get current curser position on ncurse window
		if(r-1 >= 1){
			if(c < sizes[r-2])
				move(r-1, c);			// move curser
			else if(c == sizes[r-2])
				move(r-1, c-1);
			else
				move(r-1, sizes[r-2] - 1);
			refresh();
		}
	}
	else if (ch == KEY_DOWN)
	{
		getyx(stdscr, r, c);
		if(r+1 < numLines + 1){
			if(c < sizes[r])
				move(r+1, c);
			else if(c == sizes[r])
				move(r+1, c-1);
			else
				move(r+1, sizes[r] - 1);
		}else if(r+1 == numLines + 1){
			move(r+1, 0);
		}
		refresh();
	}
	else if (ch == KEY_RIGHT)
	{
		getyx(stdscr, r, c);
		if(r != numLines + 1){
			if(c+1 < sizes[r-1]){
				move(r, c+1);
				refresh();
			}
		}
	}
	else if (ch == KEY_LEFT)
	{
		getyx(stdscr, r, c);
		if(c-1 >= 0){
			move(r, c-1);
			refresh();
		}
	}
	
	}
}
