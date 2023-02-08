#FILE: Makefile
#File Created: 17/10/2019
#Author: Denise Abalos
#______________________________
#Date last modified: 17/10/2019
#______________________________
#Purpose: To compile and combine all files together


#MAKEFILE VARIABLES
#We create these variables to avoid repetition and allow easy configuration
CC = gcc 
CFLAGS = -Wall -Werror -ansi -pedantic -g
OBJ = LinkedList.o log.o Main.o moveTest.o read.o structInitialise.o UI.o winnerTest.o
EXEC = TicTacToe

#This is used to define EDITOR and allows it to be executed in our flags
#When this is compiled it will trigger the declaration in our UI
ifdef EDITOR
CFLAGS += -D EDITOR
EDITOR : clean $(EXEC)
endif

ifdef SECRET
CFLAGS += -D SECRET
SECRET : clean $(EXEC)
endif

#Compile all our files together
$(EXEC) : $(OBJ)
		$(CC) $(OBJ) -o $(EXEC)
	
LinkedList.o : LinkedList.c TicTacToe.h
		$(CC) -c LinkedList.c $(CFLAGS)

log.o : log.c TicTacToe.h
		$(CC) -c log.c $(CFLAGS)

Main.o : Main.c TicTacToe.h
		$(CC) -c Main.c $(CFLAGS)

moveTest.o : moveTest.c TicTacToe.h
		$(CC) -c moveTest.c $(CFLAGS)

read.o : read.c TicTacToe.h
		$(CC) -c read.c $(CFLAGS)

structInitialise.o : structInitialise.c TicTacToe.h
		$(CC) -c structInitialise.c $(CFLAGS)

UI.o : UI.c TicTacToe.h
		$(CC) -c UI.c $(CFLAGS)

winnerTest.o : winnerTest.c TicTacToe.h
		$(CC) -c winnerTest.c $(CFLAGS)

#removes all generated file(onject and executable files)
clean : 
	rm -f $(EXEC) $(OBJ)
