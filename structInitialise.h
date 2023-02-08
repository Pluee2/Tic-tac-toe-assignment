#ifndef STRUCT_H
#define STRUCT_H

/*A struct that is used to store the data of each move*/
typedef struct {
    int turn;
    char player;
    int column;
    int row;
    char playWin;
    char winArr[20];
} Log;

char** boardInitializer(int*,int*,char**);

#endif
