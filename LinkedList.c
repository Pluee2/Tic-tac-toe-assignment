/*****************************************************************************
 *Author: Denise Abalos
 *DATE Last Modified: 10/19/2019
 *DATE Created : 09/27/2019
 *                  This program is from prac 7 of ucp
 *  functions added include: freeLog and printLog
 * **************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"TicTacToe.h"

/******************************************************************************
 *Function: createNode
 *IMPORT: none
 *EXPORT: created node 
 *ASSERTION: Creates a fresh node that currently points to no node
 *****************************************************************************/
LinkedListNode* createNode()
{
    LinkedListNode* node;

    /*This allocated memory to our node so that whenever we insert into our
 *  list we want to create a new node everytime to store the contents making
 *  sure we set next and prev pointer to NULL as at the moment it's not pointing
 *  at any node*/
    node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->prev = NULL;
    
    return node;
}

/******************************************************************************
 *Function: createLinkedList
 *IMPORT: none
 *EXPORT: created list that stores the node
 *ASSERTION: Creates a linked list to store node 
 *****************************************************************************/
LinkedList* createLinkedList()
{
    LinkedList* list;

    list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL; 
    list->freeL = NULL;
    list->count = 0;
    return list;   
}

/******************************************************************************
 *Function: insertStart
 *IMPORT: LinkedList* list, void* entry
 *EXPORT: node
 *ASSERTION: Inserts a created node in front of our list
 *****************************************************************************/
void insertStart(LinkedList* list, void* entry)
{
    /*Creates a node and insert it at the front of our list*/
    LinkedListNode* node;
    node = createNode();

    /*We add the data to our created node and since our data is a void* we 
 *  don't have to typecaset to a specific data type*/
    node->data = entry;

    /*We check if the list is empty meaning head is null, if it is then we assign
 *  both head and tail to the created node*/
    if(list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        /*If list isn't empty then we link the current head node and connect 
 *      to the created node before it as we're inserting from the start of
 *      our list*/
        list->head->prev = node;
        node->next = list->head;
        /*Make the created node point to the head of our list and that becomes
 *      the new head*/
        list->head = node;
    }
    list->count++;
    
}

/******************************************************************************
 *Function: insertLast
 *IMPORT: LinkedList* list, void* entry
 *EXPORT: none
 *ASSERTION: Inserts a created node at the tail of our list
 *****************************************************************************/
void insertLast(LinkedList* list, void* entry)
{
    LinkedListNode* node;
    node = createNode();

    node->data = entry;

    if(list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        /*Make the current tail of the list point at the node next to it as 
 *      that will be our new Tail*/
        list->tail->next = node;
        node->prev = list->tail;
        /*After the node has reference to the previous tail node, we make our
 *      new node the tail of the list*/
        list->tail = node;
    }
    list->count++;
}

/******************************************************************************
 *Function: removeStart
 *IMPORT: LinkedList* list
 *EXPORT: void*
 *ASSERTION: Removes the node at the start of our list and returning the data
 * that is associated with that node
 *****************************************************************************/
void* removeStart(LinkedList* list)
{
    LinkedListNode* node;
    void* temp;

    /*If the list then that means there is nothing to remove as our list is
 *  currently empty*/
    if(list->head == NULL)
    {
        puts("List is empty");
    }
    else
    {
        /*We assign the head of our list to a temporary node so we can free
 *      get rid of it*/
        node = list->head;
        /*Assign temp to the node data that we're currently removing ensuring
 *      we're removing the correct node*/
        temp = node->data;
        /*After we remove the data we make our head point to the node next to
 *      the node we're removing*/
        list->head = list->head->next;
        /*Delete the first node from memory*/
        free(node);
    }
    list->count--;
               
    return temp;
}       

/******************************************************************************
 *Function: removeLast
 *IMPORT: LinkedList* list
 *EXPORT: void*
 *ASSERTION: Removes the node at the end of our list and returning the data
 * that is associated with that node
 *****************************************************************************/
void* removeLast(LinkedList* list)
{
    LinkedListNode* node;
    void* temp;

    if(list->head == NULL)
    {
        puts("List is empty");
    }
    else
    {
        node = list->tail;
        temp = node->data;
        list->tail = list->tail->prev;
        free(node);
        list->tail->next = NULL;
    }
    list->count--;
        
    return temp;
}

/******************************************************************************
 *Function: freeLog
 *IMPORT: void*
 *EXPORT: node
 *ASSERTION: Frees the specific data type that we stored in our linked list which
 * is of type log
 *****************************************************************************/
void freeLog(void* n)
{
    free((Log*)n);
    n = NULL;   
}

/******************************************************************************
 *Function: freeLink
 *IMPORT: LinkedList* list, freeList freePtr
 *EXPORT: node
 *ASSERTION: Frees the linked list and the data type it holds. This is why we
 * pass in a function pointer so that we can free the correct data its holding
 *****************************************************************************/
void freeLink(LinkedList* list,freeList freePtr)
{
    /*The mainNode is responsible for freeing the main node that contains the 
 *  linked list as the data and mainTemp is simply a reference to the next node*/
    LinkedListNode* mainNode,*mainTemp;
    /*This inNode is then responsible for freeing the main inside node which
 *  contains our log data and inTemp is a reference to the next node*/
    LinkedListNode* inNode,*inTemp;
    
    /*Since we're storing linked list as a data for the main link list, we need
 *  another linked list which is the inSide list that contains the log data
 *  itself and retrieve it so we can access the logs*/
    LinkedList* inList;

    mainNode = list->head;

    /*So here the main list stores a linked list and each of those list is a
 *  different game, so until we reach the number of games we've played we 
 *  traverse through our list and free the inside lsit*/
    while(mainNode != NULL)
    {
        /*Point to the next node of the linked list as if free our node it 
 *      won't be pointing at anything anymmore so we need a reference to the 
 *      next node*/
        mainTemp = mainNode->next;
        
        /*Since our node data is of type linked list we typecast it so we can
 *      access the inside linked list*/
        inList = (LinkedList*)mainNode->data;
        inNode = inList->head;

        while(inNode != NULL)
        {
            inTemp = inNode->next;
            /*Here we use a function pointer that takes in a void* and free 
 *          the specific data type that we're using which is of type log*/
            (*freePtr)(inNode->data);
            free(inNode);
            inNode = inTemp;
        }

        free(inList);
        free(mainNode);
        mainNode = mainTemp;
    }
   
    /*Free the list*/ 
    free(list);
    list = NULL;
}

/******************************************************************************
 *Function: printLinkedList
 *IMPORT: LinkedList* list, printPtr print
 *EXPORT: none
 *ASSERTION: This prints the linked list by passing in a function pointer and
 * dereference the void* to log data type
 *****************************************************************************/
void printLinkedList(LinkedList* list , printPtr print)
{
    int gameNum = 1;
    LinkedList* mainList;
    LinkedListNode* mainNode,*inNode;
    mainNode = list->head;
    
    while(mainNode != NULL)
    {
        mainList = mainNode->data;
        inNode = mainList->head;
        
        printf("\nGame: %d\n" , gameNum);
        while(inNode != NULL)
        {
            /*Pass in the node data to the function pointer as the function 
 *          pointer that we created takes in a void pointer and therefore this
 *          is possible to do, what it simply does is it dereferences the
 *          void* to the data type we want to print which is of type logs*/   
            (print)(inNode->data);
            inNode = inNode->next;
        }
        printf("\n");
        gameNum++;
        mainNode = mainNode->next;
    }
}

/******************************************************************************
 *Function: printLog
 *IMPORT: void*
 *EXPORT: none
 *ASSERTION: Prints the logs inside the inner linked list we dereference the
 * data of the node to log so that we can print the actual value
 *****************************************************************************/
void printLog(void* n)
{
    Log* log = (Log*)n;

    if(log->turn != 0 || log->player != 0 || log->row != 0 || log->column != 0)
    {
        printf("\nTurn: %d\nPlayer: %c\nLocation: %d,%d\n", log->turn,log->player,log->row,log->column);
    }
    else if(log->playWin == 'X' || log->playWin == 'O')
    {
        /*GRN is simply print the text in green colour and reset is simply 
 *      turning back the colour to the default colour*/
        printf(GRN "\n\t\tPlayer %c won\n" RESET,log->playWin);
    }
    else if(log->winArr != NULL)
    {
        printf(GRN "\n\t\t%s\n" RESET, log->winArr);
    }
}

