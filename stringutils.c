//
// Created by edward on 19-3-26.
//

#include "stringutils.h"
#include <stdlib.h>

int readNextString(FILE *fileDesc, char **ptr) {
    char bufferSize = 64;
    char bufferIncreaseStep = 64;
    char charLength = 0;

    char *buffer = malloc(sizeof(char) * bufferSize);
    int data = EOF;
    char needTrimCRLF = 1;

    do {
        data = fgetc(fileDesc);
        if ((data == '\r' || data == '\n') && needTrimCRLF == 1) {
            continue;
        } else {
            needTrimCRLF = 0;
        }
        if (charLength == bufferSize) {
            char *lastBuffer = buffer;
            buffer = realloc(buffer, bufferSize + bufferIncreaseStep);
            bufferSize = bufferSize + bufferIncreaseStep;
            if (buffer == NULL) {
                free(lastBuffer);
                return 0;
            }
        }
        if (data == '\r' || data == '\n' || data == EOF) {
            buffer[charLength] = '\0';
            charLength++;
            buffer = realloc(buffer, charLength);
            *ptr = buffer;
            if (data == EOF) {
                return EOF;
            } else{
                return 0;
            }
        }

        buffer[charLength] = data;
        charLength++;
    } while (1);

}
void printBinary(char ch){
    unsigned  char p=0x80;
    while(p){
        p&ch?putchar('1'):putchar('0');
        p>>=1;
    }
}
void printStringThroughBinaryForm(char *p,int size){
    for(int i=0;i<size;i++){
        printf("[%d]",i+1);
        printBinary(p[i]);
        putchar(' ');
    }
    putchar('\n');
}
char *readAllByteFromFile(FILE *file, int *length) {
    int bufferSize = 64 * 1024;
    int bufferSizeIncrese = 64 * 1024;
    int nextInnerIndexToWrite = 0;
    char *buffer = 0;
    int readedLength = 0;

    buffer = (char *) malloc(sizeof(char) * bufferSize);
    while (0 != (readedLength = fread(buffer + nextInnerIndexToWrite, 1, bufferSize - nextInnerIndexToWrite, file))) {
        nextInnerIndexToWrite += readedLength;
        if (nextInnerIndexToWrite == bufferSize) {
            char *tempBuffer = (char *) realloc(buffer, bufferSize + bufferSizeIncrese);
            if (tempBuffer != 0) {
                buffer = tempBuffer;
                bufferSize += bufferSizeIncrese;
            } else {
                // No Memory To alloc ;
                free(buffer);
                return 0;
            }
        }
    }
    buffer = realloc(buffer, nextInnerIndexToWrite);
    *length = nextInnerIndexToWrite;
    return buffer;
}