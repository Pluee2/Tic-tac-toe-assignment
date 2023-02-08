#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"TicTacToe.h"
    
/******************************************************************************
 *Function: boardInitializer 
 *IMPORT: int*,int*,char**
 *EXPORT: void
 *ASSERTION: This initializes the board and sets an empty spaces to each section
 * of the board
 *****************************************************************************/
char** boardInitializer(int* row, int* col,char** board)
{
    int i,j;

    /*We malloc the 2d array that we are using by mallocing the rows and the
 *  columns */
    board = (char**)malloc((*row) * sizeof(char*));
    for(i = 0; i < *row; i++)
    {
        board[i] = (char*)malloc((*col) * sizeof(char));
    }

    /*After we have allocated memory to our board, we fill our board with empty
 *  spaces to use later. We use ' ' indicating that the board position is
 *  currently empty*/
    for(i = 0;i < *col ;i++)
    {
        for(j = 0;j < *row;j++)
        {
            board[j][i] = ' ';
        }
    }
    
    return board;   
    
}
