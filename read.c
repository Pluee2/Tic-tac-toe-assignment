#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"TicTacToe.h"

/******************************************************************************
 *Function: readFile
 *IMPORT: LinkedList*,int*,int*,int*,int
 *EXPORT: void
 *ASSERTION: This reads the settings file and sets is to the values of rows,col 
 * and numMatch
 *****************************************************************************/
void readFile(char** argv, int* row, int* col, int* numMatch)
{ 
    FILE* file;
    char letter;
    int count = 0, end = 0;
    int temp;
    int nRead;
    
    *row = 0;
    *col = 0;
    *numMatch = 0;
    
    file = fopen(argv[1],"r");

    if(file == NULL)
    {
        perror("Error in opening file: ");
    }
    else
    {
        while(!feof(file) && end != -1)
        {
            nRead = fscanf(file,"%c=%d\n", &letter, &temp);
            
            /*converts lowercase letter if ever the letters in the setting file
 *          is in lowercase as it's supposed to be upper by default and then 
 *          compare to M,N,K to match them to their respective owner*/
            upperIndex( &letter );
            if(temp >= 0)
            {
                count++;
                /*Here we assign the designated temp values to its owner making
 *              sure they end up at the right variable*/
                if(count <= 3)
                {
                    if( letter == 'M' )
                    {
                        *row = temp;
                        
                    }
                    else if( letter == 'N' )
                    {
                        *col = temp;
                    }
                    else if( letter == 'K' )
                    {    
                        *numMatch = temp;
                    }
                }
                else
                {
                    puts("Too many arguments in setting file");
                    end = -1;
                }
            }
            else
            {
                puts("Settings can't have 0 or negative as a value");
            }
        }

        if(nRead != 2)
        {
            puts("Error in file parsing");
        }
    }
        fclose(file);
}

/*This simply converts a string to uppercase and we use this method so that 
 * in our settings even though we do a lowercase in our settings file when
 * reading it, it will convert that lowercase to uppercase making it case
 * insensitive*/

/******************************************************************************
 *Function: upperIndex
 *IMPORT: char*
 *EXPORT: void
 *ASSERTION: This converts the lowercase to an uppercase
 *****************************************************************************/
/*This function was used in prac 4*/
void upperIndex( char *string )
{
    while(*string != '\0')
    {
        if(*string >= 'a' && *string <= 'z')
        {
           *string = *string - 32;
        }
        
        string++;
    }
}
