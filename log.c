#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include"TicTacToe.h"

/******************************************************************************
 *Function: fillLogs
 *IMPORT: int*,int*,LinkedList*,char,int*
 *EXPORT: void
 *ASSERTION: Every turn we fill our logs and assign to the player's coordinates
 * as well as the player who made the move
 *****************************************************************************/
void fillLogs(int* xCoor,int* yCoor,LinkedList* list,char playMove,int* turn)
{   
    /*Every Turn we need to create a new log so that it doesn't overwrite 
 *  every turn making sure we have different log values every turn*/
    Log* log = (Log*)malloc(sizeof(Log));

    log->turn = *turn;
    log->player = playMove;
    log->row = *xCoor;
    log->column = *yCoor;
    
    /*Insert every move to the last node of our list*/
    insertLast(list,log);
}

/******************************************************************************
 *Function: fillGame
 *IMPORT: LinkedList*,char
 *EXPORT: void
 *ASSERTION: Assign the winner of the game and we only want the player symbol
 * which is playWin and no members other than itself the reasion for 0 for others
 *****************************************************************************/
void fillGame(LinkedList* list,char player)
{
    Log* log = (Log*)malloc(sizeof(Log));

    log->turn = 0;   
    log->player = 0;
    log->row = 0;
    log->column = 0;
    log->playWin = player;

    insertLast(list,log);
}

/******************************************************************************
 *Function: fillDraw
 *IMPORT: LinkedList*
 *EXPORT: void
 *ASSERTION: Assign the winner of the game and we only want the player symbol
 * which is playWin and no members other than itself the reasion for 0 for others
 *****************************************************************************/
void fillDraw(LinkedList* list)
{
    Log* log = (Log*)malloc(sizeof(Log));

    log->turn = 0;   
    log->player = 0;
    log->row = 0;
    log->column = 0;
    log->playWin = 0;
    strcpy(log->winArr,"Game is a draw");

    insertLast(list,log);
}

/******************************************************************************
 *Function: saveLogs
 *IMPORT: LinkedList*,int*,int*,int*
 *EXPORT: void
 *ASSERTION: This function simply creates a filename to save the logs into by
 * using the current date and time
 *****************************************************************************/
void saveLogs(LinkedList* list, int* row, int* col, int* numMatch)
{
    /*Obtained from anonymous programmer,
     *      https://www.techiedelight.com/print-current-date-and-time-in-c/
     *  (accessed: 10/10/2019)
     */

    /*This stores the file name generated by the time and date*/
    char file[50];
    /*variables to store date and time components*/
    int hour,min,day,month;
    time_t currTime;
    struct tm *localTime;

    /*time() returns the current time of the system as a time_t value*/
    time( &currTime );
    /*localtime() converts a time_t value to calendar time and returns a pointer
 *  to a tm_struct with its members*/
    localTime = localtime( &currTime );
    hour = (*localTime).tm_hour;
    min = (*localTime).tm_min;
    day = (*localTime).tm_mday;
    month = (*localTime).tm_mon;
   
    sprintf(file,"MNK_%d-%d-%d_%d-%d_%d-%d.log",*row,*col,*numMatch,hour,min,day,month);
    writeFile(file,row,col,numMatch,list);
}

/******************************************************************************
 *Function: writeFile
 *IMPORT: char,int*,int*,int*,LinkedList
 *EXPORT: void
 *ASSERTION: Simply traverses through our linked list and print the values of 
 * the log into a file
 *****************************************************************************/
void writeFile(char* fileName,int* row,int* col,int* numMatch,LinkedList* list)
{
    /*Same logic as printing the linked list where we get the data of our inside 
 *  link list and retrieve the log value however here we're just writing to a
 *  file using fprintf();*/ 
    FILE* file;
    int gameNum = 1;
    Log* log;
    LinkedList* mainList;
    LinkedListNode* mainNode,*inNode;

    mainNode = list->head;

    file = fopen(fileName,"a");

    if(file == NULL)
    {
        perror("Error in opening file: ");
    }
    else
    {
        /*Print the settings at the first line of our file*/
        fprintf(file,"SETTINGS:\nM: %d\nN: %d\nK: %d\n" , *row,*col,*numMatch);
        
        while(mainNode != NULL)
        {
            mainList = mainNode->data;
            inNode = mainList->head;

            fprintf(file,"\nGame: %d\n", gameNum);

            while(inNode != NULL)
            {
                log = (Log*)inNode->data;

                /*Here we only want to print these 4 members alone without the 
 *              interferance of the playWin as well as the winArr or else if
 *              we don't do these then garbage values will be printed out
 *              for the values of playWin as well as winArr*/
                if(log->turn != 0 || log->player != 0 || log->row != 0 || log->column != 0)
                {
                    fprintf(file,"\nTurn: %d\nPlayer: %c\nLocation: %d,%d\n", log->turn,log->player,log->row,log->column);
                }
                else if(log->playWin == 'X' || log->playWin == 'O')
                {   
                    fprintf(file,"\n\t\tPlayer %c won\n",log->playWin);
                }
                else if(log->winArr != NULL)
                {
                    fprintf(file,"\n\t\t%s\n", log->winArr);
                }
                
                inNode = inNode->next;
            }
            fputs("\n",file);
            gameNum++;
            mainNode = mainNode->next;
        }

        puts("File saved successfully\n");
    }

    fclose(file);
}

/******************************************************************************
 *Function: viewLogs
 *IMPORT: int*,int*,int*,LinkedList*
 *EXPORT: void
 *ASSERTION: This simply prints the linked list which is done by just calling the
 * print function in our linked list
 *****************************************************************************/
void viewLogs(int* row,int* col,int* numMatch, LinkedList* list)
{
    printf("SETTINGS:\nM: %d\nN: %d\nK: %d\n" , *row,*col,*numMatch);
    printLinkedList(list,printLog);
}