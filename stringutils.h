//
// Created by edward on 19-3-26.
//
#include <stdio.h>
#include <stdlib.h>
#ifndef NORESPONSESERVER_STRINGUTILS_H
#define NORESPONSESERVER_STRINGUTILS_H

extern int readNextString(FILE * fileDesc,char **ptr) ;
extern void printBinary(char ch);
extern void printBinary4(int ch);
extern void printStringThroughBinaryForm(char *p,int size);
extern char *readAllByteFromFile(FILE *file, int *length);
int readAllLinesW(FILE *fileDesc, wchar_t ***lines,wchar_t **buffer);
#endif //NORESPONSESERVER_STRINGUTILS_H
