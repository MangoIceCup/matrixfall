#include<stdio.h>
#include "linkedarray.h"
#include "stringutils.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>

typedef struct _Item {
    char *stringToBeShow;
    short int nextPosition;
    short int currentPostion;
} Col;


int lengthOfCols;
int lengthOfLines;
Col *Cols;

int sizeOfString = 0;
char **sentences;


int loadString(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    int i = 0;
    if (file == NULL) {
        return 0;
    }
    Node *strings = NULL;
    char *string = NULL;
    while (EOF != readNextString(file, &string)) {
        linkArrayAppend(&strings, string);
    }
    fclose(file);
    sizeOfString = linkArraryLength(strings);
    char *p[10];
    sentences = (char **) malloc(sizeof(char *) * sizeOfString);
    for (i = 0; i < sizeOfString; i++) {
        sentences[i] = linkArrayGet(strings, i);
    }
    linkArraryDestroy(strings);
}

void RewardNumberOfColums() {
    FILE *stream;
    char buf[6];
    buf[0] = '\0';

    stream = popen("tput cols", "r");
    fscanf(stream, "%s\n", buf);
    fclose(stream);
    lengthOfCols = atoi(buf);

    stream = popen("tput lines", "r");
    fscanf(stream, "%s\n", buf);
    fclose(stream);
    lengthOfLines = atoi(buf);
}


void checkAndResetRandomString() {
    srand(time(0));
    for (int i = 0; i < lengthOfCols; i++) {
        if (Cols[i].stringToBeShow == 0 || strlen(Cols[i].stringToBeShow) == Cols[i].nextPosition) {
            if (i % 5 == 0) {
                Cols[i].stringToBeShow = sentences[rand() % sizeOfString];
                Cols[i].nextPosition = -(rand() % 8);
            } else {
                Cols[i].stringToBeShow = 0;
            }
        }
    }
}

char *readAllByteFromFile(FILE *file, int *length);

int xmain(int argumentsNumber, char *arguments[]) {
    int col_i = 0, row_i = 0;


    loadString("/home/edward/CLionProjects/NoResponseServer/msg.txt");
    RewardNumberOfColums();
    Cols = (Col *) malloc(sizeof(Col) * lengthOfCols);
    memset(Cols, 0, sizeof(Col) * lengthOfCols);
    while (1) {
        system("clear");
        checkAndResetRandomString();
        for (int i = 0; i < lengthOfCols; i++) {
            Cols[i].currentPostion = Cols[i].nextPosition;
        }
        for (row_i = 0; row_i < lengthOfLines; row_i++) {
            for (col_i = 0; col_i < lengthOfCols; col_i++) {
                char ch;
                if (Cols[col_i].stringToBeShow != NULL) {
                    if (Cols[col_i].currentPostion < 0) {
                        ch = ' ';
                    } else {
                        ch = Cols[col_i].stringToBeShow[Cols[col_i].currentPostion];
                        Cols[col_i].currentPostion--;
                    }
                } else {
                    ch = ' ';
                }
                putchar(ch);
            }
            putchar('\n');
        }
        for (int i = 0; i < lengthOfCols; i++) {
            Cols[i].nextPosition = Cols[i].nextPosition + 1;
        }
        usleep(150000);
    }
    //return 0;
}

void main(void) {
    setlocale(LC_ALL,"");
    const char *txtFilePath = "/home/edward/CLionProjects/NoResponseServer/msg.txt";
    int lengthOfFile = 0;
    unsigned char *bytesOfFile;
    int lengthOfWC=0;
    wchar_t * codepointsFromFile;

    FILE *file = fopen(txtFilePath, "rb");
    bytesOfFile = readAllByteFromFile(file, &lengthOfFile);
    fclose(file);

    if (bytesOfFile) {
        bytesOfFile = realloc(bytesOfFile, lengthOfFile + 1);
        bytesOfFile[lengthOfFile]='\0';
        lengthOfWC = mbstowcs(NULL, bytesOfFile, lengthOfFile+1);
        codepointsFromFile=(wchar_t *)malloc(sizeof(wchar_t)*(lengthOfWC+1));
        mbstowcs(codepointsFromFile,bytesOfFile,lengthOfFile+1);
        free(bytesOfFile);
        wprintf(L"%ls",codepointsFromFile);
    }
}


