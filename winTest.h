#ifndef WIN_H
#define WIN_H

int isDraw(char**,int*, int*);
int isWinner(int*,int*,int*,int*,int*,char**);
int checkRow(int, int , char**, int*, int*);
int checkCol(int,int, char**,int*,int*);
int checkDiagonal(int,int,char**, int* col, int* row, int* numMatch);
void upLeft(int, int, char**, int*);
void upRight(int, int, char**, int*, int*);
void downLeft(int, int, char**, int*, int*);
void downRight(int, int, char**, int*, int*, int*);
void checkUp(int,int,char**, int*);
void checkDown(int,int,char**,int*,int*);
void checkLeft(int, int, char**, int*);
void checkRight(int, int, char**, int*,int*);

#endif
