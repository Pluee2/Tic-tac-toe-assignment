#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

#include"TicTacToe.h"

#define PLAYER1 1
#define PLAYER2 2

#define SYMBOL1 'X'
#define SYMBOL2 'O'

/******************************************************************************
 *Function: TicTacToe
 *IMPORT: LinkedList*,int*,int*,int*,int
 *EXPORT: void
 *ASSERTION: This is the actual game where all the user inputs and stuff happens
 *****************************************************************************/
void TicTacToe(LinkedList* list,int*row,int* col,int* numMatch,int firstPlay)
{
    /*counter to keep track of the number of moves*/
    int counter = 0;
    int turn = 1;
    /*A condition to end the game if ever a player wins or draw*/
    int end = 0;
    int xPos,yPos;
    /*Empty board to initialise later*/
    char** board = NULL;
    int maxMove = (*row) * (*col);
    int playerTurn;
    char playerMove;
    
    /*
    fillSetting(list,log,row,col,numMatch);
    */

    /*used to initialise the board, this is where all the mallocs happen to 
 *  allocate memory to our board for using*/
    board = boardInitializer(row,col,board);

    /*This chooses which player goes first as in the main there is a part of
 *  code that asks the user who wants to go first, if the value is one then 
 *  player 1 will make the first move*/
    if( firstPlay == 1 )
    {
        playerMove = SYMBOL1;
        playerTurn = PLAYER1;
    }
    else    
    {
        playerMove = SYMBOL2;
        playerTurn = PLAYER2;
    }

    printf("Player %c will go first\n", playerMove);

    /*This keeps looping until the counter reaches the maxMove which is the 
 *  maximum number of moves you can do as that is the size of the board. The
 *  end is a condition that stops the loop and letting the user that they won
 *  or draw*/
    while( ( counter != maxMove ) && ( end != 1 ) )
    {
        /*prints the empty board to the user*/
        printBorder(row);
        printBoard(board,row,col);

        printf( "Player: %c to make a move: " , playerMove );
        
        do
        {
            /*Keep asking the user for the value until they input a valid move*/
            scanf( "%d,%d" , &xPos , &yPos );

            
        }while( validMove(xPos,yPos,row,col,board) != 1 && getchar() );

        /*This fills our log with the values and then inserting it to the end
 *      of our linked list for every turn*/
        fillLogs(&xPos,&yPos,list,playerMove,&turn);

        /*This simply initialises the board to the input we have placed in our
        board*/
        checkMove( xPos,yPos,board, &playerMove );


        /*This checks if a player has won, a draw or still ongoing, as we can
 *      see if both the winner and draw method matches to the boolean, it will
 *      set the end to 1 which is the exit condition of the game. Else if neither
 *      are triggered then the game still goes on until there are no more spaces
 *      in the board*/
        if( isWinner( &xPos,&yPos,row,col,numMatch,board ) == 1 )
        {
            printBorder(row);
            printBoard(board,row,col);

            printf(GRN "Player %c has won!!\n\n" RESET , playerMove);

            if( playerMove == SYMBOL1 )
            {
                fillGame(list,SYMBOL1);   
            }       
            else if( playerMove == SYMBOL2 )
            {
                fillGame(list,SYMBOL2);
            }

            end = 1;
        }
        else if( ( isDraw(board,row,col) == 1 ) || ( counter == maxMove ) ) 
        {   
        
            printBorder(row);
            printBoard(board,row,col);
            
            puts(GRN "The end result is a draw\n" RESET);
            fillDraw(list);
            end = 1;
        }
        else
        {
            /*Change the player if the player has made a move*/
            if( playerTurn == PLAYER1 )
            {   
                playerTurn = PLAYER2;
                playerMove = SYMBOL2;
            }
            else if( playerTurn == PLAYER2 )
            {
                playerTurn = PLAYER1;
                playerMove = SYMBOL1;
            }
            
            end = 0;
            turn++;
            counter++;
        }
    }

    /*After each game, the board should be free so we can allocate new 
    memory each play otherwise not freeing it will mean the board still has
    the playerMoves saved in the heap*/
    freeBoard(board,row);
}
   
/******************************************************************************
 *Function: validMove
 *IMPORT: int,int,int*,int*,char**
 *EXPORT: int
 *ASSERTION: This checks the user coordinates if they had entered an invalid
 * coordinate and checks the board if a space is occupied
 *****************************************************************************/
int validMove( int xPos, int yPos, int* row, int* col, char** board)
{
    int valid = 1;

    /*We check if both the xPos or yPos is a negative, exceeds the row and 
 *  col size as well as checking if it equals to the value of row and col
 *  as we declare our first index as 0 not 1*/
    if( ( xPos < 0 || xPos > *row || xPos == *row ) || ( yPos < 0 || yPos > *col
        || yPos == *col ) )
    {
        puts("Invalid move, select coordinates within the range of the board");
        valid = 0;
    }
    else if( board[xPos][yPos] != ' ' )
    {
        puts("The following coordinates is already occupied, choose another coordinates");
        valid = 0;
    }
    else if( board[xPos][yPos] == ' ' )
    {
        valid = 1;
    }
    
    return valid;
}

/******************************************************************************
 *Function: checkMove
 *IMPORT: int,int,char**,char*
 *EXPORT: void
 *ASSERTION: This simply sets the board to the char 'X' or 'O'
 *****************************************************************************/
void checkMove( int xPos, int yPos, char** board, char* playMove)
{
    /*Set the player symbol to the position of the inputted coordinates of 
 *  the board chosen by the user*/       
    board[xPos][yPos] = *playMove;      
}

/******************************************************************************
 *Function: printBorder
 *IMPORT: int*
 *EXPORT: void
 *ASSERTION: This prints the border of the board
 *****************************************************************************/
void printBorder(int* row)
{
    int i; 
    
    for( i = 0; i < *row; i++)
    {
        printf(MAG "====" RESET);
    }
        printf(MAG "===" RESET);
        printf("\n");
}

/******************************************************************************
 *Function: TicTacToe
 *IMPORT: LinkedList*,int*,int*,int*,int
 *EXPORT: void
 *ASSERTION: This prints the entire board based on the number of rows and col
 *****************************************************************************/
void printBoard(char** board,int* row, int* col)
{
    /*This juts prints the board when empty or has something initialised inside it
 *  I used color coded so X and O have their own colours as I think it'll be 
 *  easier to distinguish between the two*/
    int i,j;

    for( i = 0; i < *col; i++)
    {
        printf(YEL "|" RESET);
        for( j = 0; j < *row; j++ )
        {   
            printf(YEL "|   " RESET);
            
            if( board[j][i] == 'X' )
            {   
                printf(RED "\b\b%c " RESET , board[j][i]);
            }
            else if( board[j][i] == 'O' )
            {
                printf(CYN "\b\b%c " RESET, board[j][i]);
            }
        }
        printf(YEL "||\n" RESET);
        printBorder(row);
    }
        printf("\n-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n"); 
       printf("\n");
}

/******************************************************************************
 *Function: showInstructions
 *IMPORT: none
 *EXPORT: node
 *ASSERTION: This just shows how to play the game
 *****************************************************************************/
void showInstructions() 
{ 
    printf("\t\t\t    Tic Tac Toe    \n\n");   
    printf("Rules:\n");
    printf("-When prompted make a move, simply enter the coordinates corresponding to a tile of your choosing\n");
    printf("-Player will be prompted who's turn is who's. Enter coordinates in this format (1,0) or (2,3) etc\n");
    printf("-Player 1: X\n-Player 2: O\n");
    printf("-The board will initialize as below\n\n");

    printf("\t\t\t========================\n"); 
    printf("\t\t\t||  0,0 | 1,0  | 2,0  ||\n"); 
    printf("\t\t\t||--------------------||\n"); 
    printf("\t\t\t||  0,1 | 1,1  | 2,1  ||\n"); 
    printf("\t\t\t||--------------------||\n"); 
    printf("\t\t\t||  0,2 | 1,2  | 2,2  ||\n"); 
    printf("\t\t\t========================\n\n"); 
      
    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n"); 
} 

/******************************************************************************
 *Function: freeBoard
 *IMPORT: char**,int*
 *EXPORT: none
 *ASSERTION: This frees the board
 *****************************************************************************/
void freeBoard(char** board, int* row)
{
    int i;
    
    for(i = 0; i < *row;i++)
    {
        free(board[i]);
        board[i] = NULL;
    }
    free(board);
    board = NULL;
}


