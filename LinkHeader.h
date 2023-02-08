#ifndef LINK_H
#define LINK_H

/*A function pointer that frees the data of the linked list*/
typedef void (*freeList)(void *);
/*A function pointer that prints a specific data of the node*/
typedef void (*printPtr)(void *);

typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
} LinkedListNode;

typedef struct {
    LinkedListNode* head;
    LinkedListNode* tail;
    printPtr print;
    freeList freeL;
    int count;
} LinkedList;

LinkedListNode* createNode();

LinkedList* createLinkedList();

void freeLog(void*);

void freeLink(LinkedList*,freeList);

void insertStart(LinkedList* , void* );

void insertLast(LinkedList* , void* );

void* removeStart(LinkedList*);

void* removeLast(LinkedList*);

void freeLinkedList(LinkedList*,freeList);

void printLinkedList(LinkedList*, printPtr);

void printLog(void*);

#endif
