#ifndef BUFFER_H
#define BUFFER_H
#include <stdio.h>

extern FILE* fp;
extern char** buffer;
extern int* sizes;
char* line;
size_t length;
extern int numLines;

void FillBuffer();
void UpdateBuffer(int, int, int, char*, int);
void FreeBuffer();
void bufferSearch(char*, char*);

#endif
