#include "editMode.h"
#include "buffer.h"
#include <stdlib.h>
#include <ncurses.h>

void EditMode(int y, int x)
{
	cbreak();			// automatically stores key instead of having to hit enter each time
	noecho();			// handling printing to curse screen for special characters
	keypad(stdscr, TRUE);		// including keypad keys
	edited = false;
	string = NULL;
	move(y, x);

	while ( (ch = getch()) != 27)			// while not esc key
	{
		if (ch == KEY_UP)		// checking for special keys
		{
			getyx(stdscr, r, c);		// get current curser position on ncurse window

			if(edited){	
				UpdateBuffer(3, r-1, stringstart, string, size);
				free(string);
				string = NULL;
				edited = 0;
			}

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

			if(edited){
				UpdateBuffer(3, r-1, stringstart, string, size);
				free(string);
				string = NULL;
				edited = 0;
			}

			if(r+1 < numLines + 1){
				if(c < sizes[r])
					move(r+1, c);
				else if(c == sizes[r])
					move(r+1, c-1);
				else
					move(r+1, sizes[r] - 1);
			}
			refresh();
		}
		else if (ch == KEY_RIGHT)
		{
			getyx(stdscr, r, c);

			if(edited){
				UpdateBuffer(3, r-1, stringstart, string, size);
				free(string);
				string = NULL;
				edited = 0;
			}

			if(c+1 < sizes[r-1]){
				move(r, c+1);
				refresh();
			}
		}
		else if (ch == KEY_LEFT)
		{
			getyx(stdscr, r, c);

			if(edited){
				UpdateBuffer(3, r-1, stringstart, string, size);
				free(string);
				string = NULL;
				edited = 0;
			}

			if(c-1 >= 0){
				move(r, c-1);
				refresh();
			}
		}
		else if (ch == KEY_BACKSPACE || ch == KEY_DC || ch == 127) // checking for backspace key
		{
			getyx(stdscr, r, c); 

			if(edited){
				UpdateBuffer(3, r-1, stringstart, string, size);
				free(string);
				string = NULL;
				edited = 0;
			}

			if(c > 0){
				UpdateBuffer(4, r-1, c-1, NULL, 0);
				move(r, c-1);
				delch();				// deleting current key and allocating empty space
			}
			refresh();
		}
		else
		{
			getyx(stdscr, r, c);

			if(!edited){
				edited = 1;
				string = malloc(256*sizeof(char));
				size = 0;
				stringstart = c;
			}

			string[size] = ch;
			size++;
			insch(ch);				// add key to curse window
			move(r, c+1);
			refresh();
		}
	}

	if(edited){
		UpdateBuffer(3, r-1, stringstart, string, size);
		free(string);
		string = NULL;
		edited = 0;
	}

}
