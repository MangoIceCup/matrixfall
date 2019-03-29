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
#include <math.h>

typedef struct _Item {
    wchar_t *stringToBeShow;
    short int nextPosition;
} Col;


int lengthOfCols;
int lengthOfLines;
Col *Cols;

int countOfString = 0;
wchar_t **sentences;
wchar_t *allSetneces;

wchar_t **terminalBuffer;


int loadString(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return 0;
    }
    if (countOfString = readAllLinesW(file, &sentences, &allSetneces)) {
        fclose(file);
        return 1;
    } else {
        fclose(file);
        return 0;
    }
}

void RewardNumberOfColums() {
    FILE *stream;
    char buf[6];
    buf[0] = '\0';

    stream = popen("tput cols", "r");
    fscanf(stream, "%s\n", buf);
    fclose(stream);
    lengthOfCols = atoi(buf) / 2;

    stream = popen("tput lines", "r");
    fscanf(stream, "%s\n", buf);
    fclose(stream);
    lengthOfLines = atoi(buf);
}

void createTerminalBuffer(wchar_t ***screenBuffer, int rows, int colums) {
    *screenBuffer = (wchar_t **) malloc(sizeof(wchar_t *) * rows);
    memset(*screenBuffer, 0, sizeof(wchar_t *) * rows);
    for (int i = 0; i < rows; i++) {
        wchar_t *p = (wchar_t *) malloc(sizeof(wchar_t) * colums);
        memset(p, 0, sizeof(wchar_t) * colums);
        (*screenBuffer)[i] = p;

    }
}

void displayScreenBuffer(wchar_t **screenBuffer, int rows, int colums) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colums; j++) {
            wchar_t ch = screenBuffer[i][j];
            // wprintf(L"(%d,%d):", i, j);
            // printBinary4(ch);
            if (ch == ' ' || ch == 0) {
                putwchar(' ');
                putwchar(' ');
            } else if (ch < 128) {
                putwchar(ch);
                putwchar(' ');
            } else {
                putwchar(ch);
            }
        }
        putwchar('\n');
    }
    fflush(stdout);
}

void updateScreenBuffer(wchar_t **screenBuffer, int rows, int colums, Col *cols) {
    for (int i = 0; i < colums; i++) {
        if (cols[i].stringToBeShow == 0) {
            screenBuffer[rows - 1][i] = 0;
        } else {
            if (cols[i].nextPosition < 0) {
                screenBuffer[rows - 1][i] = 0;
                cols[i].nextPosition++;
            } else {
                screenBuffer[rows - 1][i] = cols[i].stringToBeShow[cols[i].nextPosition++];
            }
        }
    }
    wchar_t *lastRow = screenBuffer[rows - 1];
    for (int i = rows - 1; i > 0; i--) {
        screenBuffer[i] = screenBuffer[i - 1];
    }
    screenBuffer[0] = lastRow;
}

int countOfValidCol(Col const *cols, const int lengthOfCols) {
    int result = 0;
    for (int i = 0; i < lengthOfCols; i++) {
        if (cols[i].stringToBeShow != 0 && wcslen(cols[i].stringToBeShow) != cols[i].nextPosition) {
            result++;
        }
    }
    return result;
}

void checkAndResetRandomString(Col *cols, int const lengthOfCols, wchar_t **const sentences, int countOfSentences) {
    srand(time(0));
    for (int i = 0; i < lengthOfCols; i++) {
        if (cols[i].stringToBeShow != 0 && wcslen(cols[i].stringToBeShow) == cols[i].nextPosition) {
            cols[i].stringToBeShow = 0;
            cols[i].nextPosition = 0;
        }
    }
    while (countOfValidCol(cols, lengthOfCols) < (int) ceil(0.4 * lengthOfCols)) {
        int randomIndex = 0;
        for (randomIndex = rand() % lengthOfCols;
             cols[randomIndex].stringToBeShow != 0;
             randomIndex = rand() % lengthOfCols);
        cols[randomIndex].stringToBeShow = sentences[rand() % countOfSentences];
        cols[randomIndex].nextPosition = -(abs(rand() % 6)+6);
    }
}


int main(int argumentsNumber, char *arguments[]) {
    setlocale(LC_ALL, "");
    loadString("/home/edward/CLionProjects/NoResponseServer/msg.txt");
    RewardNumberOfColums();
    Cols = (Col *) malloc(sizeof(Col) * lengthOfCols);
    memset(Cols, 0, sizeof(Col) * lengthOfCols);
    createTerminalBuffer(&terminalBuffer, lengthOfLines, lengthOfCols);
    while (1) {
        system("clear");
        checkAndResetRandomString(Cols, lengthOfCols, sentences, countOfString);
        updateScreenBuffer(terminalBuffer, lengthOfLines, lengthOfCols, Cols);
        displayScreenBuffer(terminalBuffer, lengthOfLines, lengthOfCols);
        usleep(180000);
    }
}



