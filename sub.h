/**
 * C program to find and replace all occurrences of a word in file.
Thanks to Pankaj Prakash (codeforwin) for his version, inspiring the below.
 Modified for use in W 2.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100000

/* Function declaration */
void replaceAll(char *str, char *oldWord, char *newWord);


void sub( char path[1000], char oldWord[1000], char newWord[1000] )
{

    /* File pointer to hold reference of input file */
    FILE * fPtr;
    FILE * fTemp;
    
    char buffer[BUFFER_SIZE];


    /*  Open all required files */
    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given %e. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }


    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        // Replace all occurrence of word from current line
        replaceAll(buffer, oldWord, newWord);

        // After replacing write it to temp file.
        fputs(buffer, fTemp);
    }

    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

	remove(path);

    /* Rename temp file as original file */
    rename("replace.tmp", path);

    printf("\nSuccessfully replaced all occurrences of '%s' with '%s'.", oldWord, newWord);

}















/**
 * Replace all occurrences of a given a word in string.
 */
void replaceAll(char *str, char *oldWord, char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);


    /*
     * Repeat till all occurrences are replaced. 
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Bakup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;

        // Terminate str after word found index
        str[index] = '\0';

        // Concatenate str with new word 
        strcat(str, newWord);
        
        // Concatenate str with remaining words after 
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}
