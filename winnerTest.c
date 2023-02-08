#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"TicTacToe.h"

/******************************************************************************
 *Function: isDraw
 *IMPORT: char**,int*,int*
 *EXPORT: int
 *ASSERTION: A function that determines if neither player won the match as if
 * the board is all filled out, then draw will return 1 and indicating a draw
 *****************************************************************************/
int isDraw(char** board,int* row, int* col)
{
    /*We make the default value one meaning that there are no more squares to
 *  fill out in our game and therefore ends in a draw*/ 
    int i,j,draw = 1;
    
    for(i = 0; i < *col; i++)
    {
        for(j = 0; j < *row; j++)
        {
            if(board[j][i] == ' ')
            {
                /*The square still contains some empty spaces and therefore
                game is still not over*/
                draw = 0;
            }
        }
    }

        return draw;
}


/******************************************************************************
 *Function: isWinner
 *IMPORT: int*,int*,int*,int*,int*,char**
 *EXPORT: int
 *ASSERTION: A function that determines which player won the game by checking
 * each of possible direction 
 *****************************************************************************/
int isWinner(int* xCoor,int* yCoor,int* row,int* col,int* numMatch,char** board)
{
    int win = 0;
    int xPos = *xCoor;
    int yPos = *yCoor;

    /*Checks these functions if they return 1 meaning there is a streak of X or
 *  O, if one of these functions is triggered then that means the player whoever
 *  got the streaks won the match*/
    if( (checkRow(xPos,yPos,board,row,numMatch) == 1) || 
    (checkDiagonal(xPos,yPos,board,row,col,numMatch) == 1) || 
    (checkCol(xPos,yPos,board,col,numMatch) == 1 ))
    {
        win = 1;
    }

    return win;
}
 
/******************************************************************************
 *Function: checkRow
 *IMPORT: int,int,char**,int*,int*
 *EXPORT: int
 *ASSERTION: A function that checks the row,this checks the left direction as
 * well as the right direction checking if we've got a streak of 'X' or 'O'
 *****************************************************************************/
int checkRow(int x, int y, char** board, int* row, int* numMatch)
{
    int end = 0;
    int count = 1;
    
    checkLeft(x,y,board,&count);
    checkRight(x,y,board,&count,row);   
    if( count >= *numMatch )
    {
        end = 1;
    }
    

    return end;
}

/******************************************************************************
 *Function: checkCol
 *IMPORT: int,int,char**,int*,int*
 *EXPORT: int
 *ASSERTION: A function that checks the column,this checks the up direction as
 * well as down direction checking if we've got a streak of 'X' or 'O'
 *****************************************************************************/
int checkCol(int x,int y, char** board, int* col, int* numMatch)
{
    int end = 0;
    int count = 1;

    checkDown(x,y,board,&count,col);
    checkUp(x,y,board,&count);
    if( count >= *numMatch )
    {
        end = 1;
    }

    return end;
}

/******************************************************************************
 *Function: checkDiagonal
 *IMPORT: int,int,char**,int*,int*,int*
 *EXPORT: int
 *ASSERTION: A function that checks every diagonal,this checks the main diagonal as
 * well as the anti direction checking if we've got a streak of 'X' or 'O'
 *****************************************************************************/
int checkDiagonal(int x, int y, char** board, int* col, int* row, int* numMatch)
{
    int end = 0;
    int count = 1;
    
    upLeft(x,y,board,&count);
    downRight(x,y,board,&count,row,col);
    if( count >= *numMatch )
    {
        end = 1;
    }
    else
    {
        /*reset count by 1 as it's been modified by the recursions above*/
        count = 1;  
        upRight(x,y,board,&count,row);
        downLeft(x,y,board,&count,col);
        if( count >= *numMatch )
        {
            end = 1;
        }
    }

    return end;
}       

/******************************************************************************
 *Function: upLeft
 *IMPORT: int,int,char**,int*
 *EXPORT: none
 *ASSERTION: Using recursion we check the upLeft diagonal and keep recurssing 
 * if there's a match and end until we get to the base case 
 *****************************************************************************/
/* 
 *| X |   |   |  
 *-------------
 *|   | X |   |  
 *-------------
 *|   |   | X |  
 *-------------
 * checks down direction*/
void upLeft(int x, int y, char** board, int* count)
{
    if( x == 0 || y == 0 )
    {
        /*Base condition to end recursion*/
    }
    else if(board[x][y] == board[x-1][y-1])
    {
        (*count)++;
        upLeft(x-1,y-1,board,count);
    }
}

/******************************************************************************
 *Function: upRight
 *IMPORT: int,int,char**,int*,int*
 *EXPORT: none
 *ASSERTION: Using recursion we check the upRight diagonal and keep recurssing 
 * if there's a match and end until we get to the base case 
 *****************************************************************************/
/* 
 *|   |   | X |  
 *-------------
 *|   | X |   |  
 *-------------
 *| X |   |   |  
 *-------------
 * checks down direction*/
void upRight(int x, int y, char** board, int* count, int* row)
{
    if( x == *row - 1 || y == 0 )
    {
        /*Base condition to end recursion*/
    }
    else if(board[x][y] == board[x+1][y-1])
    {
        (*count)++;
        upRight(x+1,y-1,board,count,row);
    }
}

/******************************************************************************
 *Function: 
 *IMPORT: int,int,char**,int*,int*
 *EXPORT: none
 *ASSERTION: Using recursion we check the downLeft diagonal and keep recurssing 
 * if there's a match and end until we get to the base case 
 *****************************************************************************/
/* 
 *|   |   | X |  
 *-------------
 *|   | X |   |  
 *-------------
 *| X |   |   |  
 *-------------
 * checks downLeft direction*/
void downLeft(int x, int y, char** board, int* count, int* col)
{
    if( y == *col - 1 || x == 0 )
    {
        /*Base condition to end recursion*/
    }
    else if( board[x][y] == board[x-1][y+1])
    {
        (*count)++;
        downLeft(x-1,y+1,board,count,col);
    }
}

/******************************************************************************
 *Function: downRight
 *IMPORT: int,int,char**,int*,int*,int*
 *EXPORT: none
 *ASSERTION: Using recursion we check the downRight diagonal and keep recurssing 
 * if there's a match and end until we get to the base case 
 *****************************************************************************/
/* 
 *| X |   |   |  
 *-------------
 *|   | X |   |  
 *-------------
 *|   |   | X |  
 *-------------
 * checks main diagonal direction*/
void downRight(int x, int y, char** board, int* count, int* row, int* col)
{
    if( x == *row - 1 || y == *col - 1 )
    {
        /*Base condition to end recursion*/
    }
    else if(board[x][y] == board[x+1][y+1])
    {
        (*count)++;
        downRight(x+1,y+1,board,count,row,col);
    }
}

/******************************************************************************
 *Function: checkUp
 *IMPORT: int,int,char**,int*
 *EXPORT: none
 *ASSERTION: Using recursion we check the up direction of the board 
 * and keep recurssing if there's a match and end until we get to the base case 
 *****************************************************************************/
/* 
 *| X |   |   |  ↑
 *-------------
 *| X |   |   |  ↑
 *-------------
 *| X |   |   |  ↑
 *-------------
 * checks down direction*/
void checkUp(int x,int y,char** board, int* count)
{
    if( y == 0 )
    {
        /*Base condition to end recursion*/
    }
    else if(board[x][y] == board[x][y-1])
    {
        (*count)++;
        checkUp(x,y-1,board,count);
    }      
}

/******************************************************************************
 *Function: checkDown
 *IMPORT: int,int,char**,int*,int*
 *EXPORT: none
 *ASSERTION: Using recursion we check down direction and keep recurssing 
 * if there's a match and end until we get to the base case 
 *****************************************************************************/
/* 
 *| X |   |   |  ↓
 *-------------
 *| X |   |   |  ↓
 *-------------
 *| X |   |   |  ↓
 *-------------
 * checks down direction*/
void checkDown(int x,int y,char** board,int* count,int* col)
{
    if( y == *col - 1)
    {
    }
    else if(board[x][y] == board[x][y+1])
    {
        (*count)++;
        checkDown(x,y+1,board,count,col);
    }        
}

/******************************************************************************
 *Function: checkLeft
 *IMPORT: int,int,char**,int*
 *EXPORT: none
 *ASSERTION: Using recursion we check the left direction and keep recurssing 
 * if there's a match and end until we get to the base case 
 *****************************************************************************/
/*  <-  <-  <-
 *| X | X | X |
 *-------------
 *|   |   |   |
 *-------------
 *|   |   |   |
 *-------------
 * checks this direction*/
void checkLeft(int x, int y, char** board, int* count) 
{
    if( x == 0 )
    {
        /*Base condition to stop the recursion*/
    }
    else if(board[x][y] == board[x-1][y])
    {
        (*count)++;
        checkLeft(x-1,y,board,count);
    }
}
 
/******************************************************************************
 *Function: checkRight
 *IMPORT: int,int,char**,int*,int*
 *EXPORT: none
 *ASSERTION: Using recursion we check the right direction and keep recurssing 
 * if there's a match and end until we get to the base case 
 *****************************************************************************/
/* ->  ->  ->
 *| X | X | X |
 *-------------
 *|   |   |   |
 *-------------
 *|   |   |   |
 *-------------
 * checks this position*/
void checkRight(int x, int y, char** board, int* count,int* row)
{
    if( x == *row - 1)
    {
        /*Base condition to stop the recursion*/
    }
    else if( board[x][y] == board[x+1][y] )
    {
        (*count)++;
        checkRight(x+1,y,board,count,row);
    }
}   
       
