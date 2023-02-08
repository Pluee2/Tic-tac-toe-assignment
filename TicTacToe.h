#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include"LinkHeader.h"
#include"UI.h"
#include"structInitialise.h"
#include"winTest.h"
#include"color.h"

void viewLogs(int*,int*,int*,LinkedList*);

void fillLogs(int*,int*,LinkedList*,char,int*);

void writeFile(char*,int*,int*,int*,LinkedList*);

void fillGame(LinkedList*,char);

void fillDraw(LinkedList*);

void saveLogs(LinkedList*,int*,int*,int*);

void randWinner();

int validMove( int, int, int*, int*, char** );

void TicTacToe(LinkedList*,int*,int*,int*,int);

void printBoard(char**,int*,int*);

void checkMove( int, int, char**, char* );

void freeBoard(char**,int*);

void showInstructions();

void readFile(char**,int*, int*,int*);

void upperIndex( char *string );

void printBorder(int*);
#endif
