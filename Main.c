/*****************************************************************************
 *Author: Denise Abalos
 *DATE Last Modified: 10/21/2019
 *DATE Created : 10/6/2019
 ****************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#include "TicTacToe.h"

int main( int argc,char* argv[] )
{   
    int row,col,numMatch;

    if( argc == 1 )
    {
        puts("No command line argument is passed except for the program name");
    }
    else if( argc >= 2 )
    {
        readFile(argv,&row,&col,&numMatch);
        /*We can't have 2 as row and column as no one will win if that happens
 *      , we also can't have 2 as the num matches to win the game as the 3rd 
 *      move will surely make the player who goes first win the game no matter
 *      what*/
        if( row <= 2 || col <= 2 || numMatch <= 0 || numMatch == 2)
        {
            puts("Can't have 0 or 2 as a value for M,N or K as well al a winCondition of 2");
        }
        else
        {
            /*If we pass the test and the values are acceptable then we pass it
 *          to our menu so that we can use it to display,initialise our board etc..*/
            menu( &row,&col,&numMatch,argv );
        } 
    }

    return 0;
}

