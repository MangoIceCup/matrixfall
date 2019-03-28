//
// Created by edward on 19-3-26.
//

#include "stringutils.h"
#include <stdlib.h>
#include "linkedarray.h"

int readAllLinesW(FILE *fileDesc, wchar_t ***lines,wchar_t **buffer) {
    int lengthOfFile = 0;
    unsigned char *bytesOfFile;
    int lengthOfWC = 0;
    wchar_t *codepointsFromFile;

    bytesOfFile = readAllByteFromFile(fileDesc, &lengthOfFile);
    if (!bytesOfFile)return EOF;
    bytesOfFile = realloc(bytesOfFile, lengthOfFile + 1);
    bytesOfFile[lengthOfFile] = '\0';
    lengthOfWC = mbstowcs(NULL, bytesOfFile, lengthOfFile + 1);
    codepointsFromFile = (wchar_t *) malloc(sizeof(wchar_t) * (lengthOfWC + 1));
    mbstowcs(codepointsFromFile, bytesOfFile, lengthOfFile + 1);
    free(bytesOfFile);
    *buffer=codepointsFromFile;
    {
        Node *ptrHead = 0;
        int index = 0;

        while (codepointsFromFile[index] != 0) {
            //escape CRLF;
            while (codepointsFromFile[index] == '\r' || codepointsFromFile[index] == '\n') {
                index++;
            }

            if (codepointsFromFile[index] == 0) {
                break;
            }

            linkArrayAppend(&ptrHead, codepointsFromFile + index);
            while (codepointsFromFile[index] != '\r' || codepointsFromFile[index] != '\n' ||
                   codepointsFromFile[index] != 0) {
                index++;
            }
            if (codepointsFromFile[index] == 0) {
                break;
            }
            codepointsFromFile[index] = 0;
            index++;
        }
        if(ptrHead==0){
            *buffer=0;
            *lines=0;
            return 0;
        }else{
            int countOfValidLine=linkArraryLength(ptrHead);
            Node *temp_ptrHead=ptrHead;
            int index=0;
            *lines=(wchar_t **)malloc(sizeof(wchar_t *)*countOfValidLine);
            while (temp_ptrHead!=NULL){
                (*lines)[index]=(wchar_t *)temp_ptrHead->data;
                temp_ptrHead=temp_ptrHead->next;
                index++;
            }
            linkArraryDestroy(ptrHead);
            return 1;
        }
    }

}


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
            } else {
                return 0;
            }
        }

        buffer[charLength] = data;
        charLength++;
    } while (1);

}

void printBinary(char ch) {
    unsigned char p = 0x80;
    while (p) {
        p & ch ? putchar('1') : putchar('0');
        p >>= 1;
    }
}

void printStringThroughBinaryForm(char *p, int size) {
    for (int i = 0; i < size; i++) {
        printf("[%d]", i + 1);
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