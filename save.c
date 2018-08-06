#include "save.h"
#include "buffer.h"
#include <ncurses.h>
#include <stdlib.h>

void Save(char * file)
{
	fp = fopen(file, "w");
	fseek (fp, 0, SEEK_SET);	

	for (int i=0; i<numLines; i++) 
	{
		for(int j = 0; j < sizes[i]; j++){
			fputc(buffer[i][j], fp);
		}
	}
	fclose(fp);
	fp = NULL;
}
