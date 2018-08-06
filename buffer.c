#include <stdlib.h>
#include <string.h>
#include "buffer.h"

FILE* fp = NULL;
int numLines = 0;
char** buffer = NULL;
int* sizes = NULL;

void FillBuffer(char* file)
{
	fp = fopen(file, "r");
	if (fp)
	{
		size_t linesize;
		int i = 0;
		while(getline(&line, &length, fp) != EOF){
			numLines++;
		}
		buffer = malloc(numLines*sizeof(char*));
		sizes = malloc(numLines*sizeof(int));
		fseek(fp, 0, SEEK_SET);
		while((linesize = getline(&line, &length, fp)) != EOF){
			buffer[i] = malloc(linesize*sizeof(char));
			sizes[i] = linesize;
			strncpy(buffer[i], line, linesize);
			i++;
		}
		fclose(fp);
	}
	fp = NULL;
}

void UpdateBuffer(int method, int linenumber, int charnumber, char* string, int size){
	if(method == 1){//delete line
		char** tempbuf = buffer;
		int* tempsize = sizes;
		buffer = malloc((numLines-1)*sizeof(char*));
		sizes = malloc((numLines-1)*sizeof(int));
		int i = 0, j = 0;
		while(i < numLines){
			if(i != linenumber){
				buffer[j] = tempbuf[i];
				sizes[j] = tempsize[i];
				j++;
			}
			i++;
		}
		free(tempbuf[linenumber]);
		tempbuf[linenumber] = NULL;
		free(tempbuf);
		tempbuf = NULL;
		free(tempsize);
		tempsize = NULL;
		numLines--;
	}else if(method == 2){//insert line
		char** tempbuf = buffer;
		int* tempsize = sizes;
		buffer = malloc((numLines+1)*sizeof(char*));
		sizes = malloc((numLines+1)*sizeof(int));
		int i = 0, j = 0;
		while(i < numLines+1){
			if(i != linenumber){//copy the existing line
				buffer[i] = tempbuf[j];
				sizes[i] = tempsize[j];
				j++;
			}
			i++;
		}
		buffer[linenumber] = malloc(sizeof(char));
		strncpy(buffer[linenumber], string, 1);
		sizes[linenumber] = 1;
		free(tempbuf);
		tempbuf = NULL;
		free(tempsize);
		tempsize = NULL;
		numLines++;
	}else if(method == 3){//update line with contents
		char* templine = buffer[linenumber];
		buffer[linenumber] = malloc((sizes[linenumber]+size)*sizeof(char));
		int j = 0;
		for(int i = 0; i < charnumber; i++){
			buffer[linenumber][i] = templine[j];
			j++;
		}
		int k = 0;
		for(int i = charnumber; i < charnumber + size; i++){
			buffer[linenumber][i] = string[k];
			k++;
		}
		for(int i = charnumber + size; i < sizes[linenumber] + size; i++){
			buffer[linenumber][i] = templine[j];
		}
		free(templine);
		templine = NULL;
		sizes[linenumber] += size;
	}else if(method == 4){//delete character from line
		char* templine = buffer[linenumber];
		buffer[linenumber] = malloc((sizes[linenumber]-1)*sizeof(char));
		int i = 0, j = 0;
		while(i < sizes[linenumber]){
			if(i != charnumber){
				buffer[linenumber][j] = templine[i];
				j++;
			}
			i++;
		}
		free(templine);
		templine = NULL;
		sizes[linenumber]--;
	}else if(method == 5)	//search and replace
	{
		char* templine = buffer[linenumber];
		buffer[linenumber] = malloc((sizes[linenumber]+size)*sizeof(char));

		int j = 0;
		for (int i = 0; i < charnumber; i++)
		{
			buffer[linenumber][i] = templine[j];
			j++;
		}

		int k = 0;
		for(int i = charnumber; i < charnumber + strlen(string); i++)
		{
			buffer[linenumber][i] = string[k];
			k++;
		}

		for(int i = charnumber + strlen(string); i < sizes[linenumber] + size; i++)
		{
			buffer[linenumber][i] = templine[j + strlen(string) - size];
			j++;
		}

		free(templine);
		templine = NULL;
		sizes[linenumber] += size;
	}
}

void bufferSearch(char* stringSearch, char* stringReplace)
{
	for(int row = 0; row < numLines; row++)
	{
		for(int col = 0; col < sizes[row]; col++)
		{
			if(buffer[row][col] == stringSearch[0])
			{
				int match = 1;
				for(int k = 0; k < strlen(stringSearch); k++)
				{
					if(buffer[row][col+k] != stringSearch[k])
					{
						match = 0;
						break;
					}
				}
				if (match)
				{
					int difference = strlen(stringReplace) - strlen(stringSearch);
					UpdateBuffer(5, row, col, stringReplace, difference);
				}
			}	
		}
	}
}

void FreeBuffer(){
	for(int i = 0; i < numLines; i++){
		free(buffer[i]);
	}
	free(buffer);
	free(sizes);
	buffer = NULL;
	sizes = NULL;
}

