#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"TicTacToe.h"


/******************************************************************************
 *Function: menu
 *IMPORT: int*,int*,int*,char**
 *EXPORT: none
 *ASSERTION: The menu is simply the choices that the user can make to play,read
 * etc.
 *****************************************************************************/
void menu(int* row,int* col,int* numMatch,char** argv)
{
    int choice,turn;
    
    /*Here the list is the main linked list that we're using and since we're
 *  doing a linked list inside a linked list where the inner list represents
 *  each game*/
    LinkedList* list,*inList = NULL;

    /*The list node on the other hand is the node that will hold the linkedList
 *  values as each node is a list*/ 
    LinkedListNode* inNode = NULL;

    list = createLinkedList();

    
    do
    {
        printf("Choose between the following options\n" "1:Play game\n" 
                "2:View settings of the game\n" "3:View current logs\n"
                "4:Save log to file\n" "5:View Instructions\n"
                "6:Exit the application\n");

        scanf("%d",&choice);

            switch(choice)
            {
                case 1:
                
                turn = firstTurn();
                /*So every game we create the inner list that holds each game
 *              elements which contains the log files*/
                inList = createLinkedList();
                insertLast(list,inList);
                /*Here we need to get the tail of the mainLinked list so we
 *              can use that to pass to our game and fill that linked list of 
 *              type log*/
                inNode = list->tail;
                TicTacToe((LinkedList*)inNode->data,row,col,numMatch,turn);
                break;

                case 2:                
                
                /*As said in the assignment spec we can only change the setting
 *              during run time if we are in editor mode and therefore we need
 *              to use ifdef so if we compile with Editor defined then we can
 *              change settings during run time*/
                #ifdef EDITOR                   
                printSettings(row,col,numMatch);
                #else
                puts("Not in editor mode, cannot change settings now");
                printf("Current Settings of game:\n" "M: %d\n" "N: %d\n" "K: %d\n" , *row,*col,*numMatch);
                #endif 

                break;

                case 3:
                
                viewLogs(row,col,numMatch,list);

                break;

                case 4:
    
                #ifdef SECRET
                puts("Currently in SECRET mode, can't save to logfile");
                #else
                saveLogs(list,row,col,numMatch);
                #endif
            
                break;
        
                case 5:
        
                /*Before playing the game, showing the instructions is better so players 
                will know what to do*/
                showInstructions();
                
                break;

                case 6:
    
                    puts("Thank you");
        
                break;

                default:
    
                    puts("Invalid input, choice must be an integer");
            
            }
    }while(choice != 6 && getchar() );

    freeLink(list,freeLog);
}

/******************************************************************************
 *Function: printSettings
 *IMPORT: int*,int*,int*
 *EXPORT: none
 *ASSERTION: This prints the settings of the game as well as the ability to 
 * change the settings during run time
 *****************************************************************************/
void printSettings(int* row, int* col, int* numMatch)
{
    int choice;
    int end = 0;
    printf("Current Settings of game:\n" "M: %d\n" "N: %d\n" "K: %d\n" , *row,*col,*numMatch);
    puts("Would you like to change the settings of the board?");
 
    do
    {
        puts("1: Change setting\n2: Keep Setting");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                changeSetting(row,col,numMatch);
                end = 1;
                break;

            case 2:
                puts("Settings have not been changed");
                end = 1;
                break;

            default:
                puts("Enter choice of only 1 or 2");
        }
    }while( end == 0 );
}                

/******************************************************************************
 *Function: changeSetting
 *IMPORT: int*,int*,int*
 *EXPORT: none
 *ASSERTION: Changes the current settings to a new one for the game
 *****************************************************************************/
void changeSetting(int* row, int* col,int* numMatch)
{
    int width,height,match;

    /*We check if the settings changed by the user is valid, if not then we 
 *  keep on prompting the user unti the settings is valid*/
    do
    {
        puts("Enter the new value for row");
        scanf("%d",&width);
        puts("Enter the new value for column");
        scanf("%d",&height);
        puts("Enter how many matching streak for user to win");
        scanf("%d",&match);
    
    }while( validChange(width,height,match) != 1 );
   
    *col = height;
    *row = width;
    *numMatch = match;
}

/******************************************************************************
 *Function: validCahnge
 *IMPORT: int,int,int
 *EXPORT: int
 *ASSERTION: This is just checks whether the new settings that we inputted is a
 * valid change
 *****************************************************************************/
int validChange(int width,int height, int match)
{
    int valid = 1;

    if( width <= 2 || height <= 2  || match < 0 || match == 2 )
    {
        puts("Can't have 0 as value or number matches equal to 2");
        valid = 0;
    }

    return valid;
}

/******************************************************************************
 *Function: firstTurn
 *IMPORT: none
 *EXPORT: int
 *ASSERTION: A function that determines which player goes first in the game
 *****************************************************************************/
int firstTurn()
{
    int firstMove,firstPlayer;

    do
    {
        puts("Choose the player who will go first\n""1:Player 1\n" "2:Player 2"); 
        scanf("%d",&firstMove);

        if( firstMove < 0 || firstMove > 2 )
        {
            puts("Only choose between 1 and 2");
        }
        else if(firstMove == 1)
        {
            firstPlayer = firstMove;
        }
        else
        {
            firstPlayer = firstMove;
        }

    }while( firstMove < 0 || firstMove > 2 ); 

    return firstPlayer;
}

