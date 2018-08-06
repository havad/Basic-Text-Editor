#include "searchAndReplace.h"
#include "buffer.h"
#include "displayText.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

void searchAndReplace()
{
	//moves cursor to last line to give visual cue
	move(LINES-1, 16);
	printw("String to Replace: ");	

	//input isn't shown until enter is pressed but takes the desired search
	//term as iput 
	mvscanw(LINES-1, 35, "%s", strSearch);
	move(LINES-1, 35);
	printw("'%s' will be replaced with: ", strSearch);
	refresh();
	strlength = strlen(strSearch);
	
	//take the replacement term as input
	move(LINES-1, 35 + strlength + 26);
	refresh();
	mvscanw(LINES-1, 35+ strlength +26, "%s", strReplace);
	move(LINES-1, 35 + 26 + strlength);
	printw("'%s'", strReplace);
	refresh();	

	move(1,0);
	refresh();

	bufferSearch(strSearch, strReplace);
	DisplayText();
}
