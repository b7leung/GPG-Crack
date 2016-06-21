#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "crackConstants.h"

// global start and end charachters representing the 
// range of possible password chars.
char START_CHAR;
char END_CHAR;

/*
 * Method Name: main
 * Description: Main driver for Crack. Checks for flags, then uses
 * brute-force to discover the correct password for a gpg symetrically
 * locked file (via gpg -c filename_here). 
 * Parameter(s): Command-line arguments. 
 * Side Effect(s): Results of crack are printed. 
 * Return: EXIT_FAILURE if errors were encounted, EXIT_SUCCESS otherwise.
 */

int main( int argc, char * argv[] ){

  // Records time taken to crack
  struct timespec startTime;
  struct timespec endTime;
  clock_gettime( CLOCK_MONOTONIC, &startTime);

  // parsing arguments 
  int args = parseArgs(argc, argv);
  
  // checking for invalid flags
  if( args & ERR_FLAG ){
    fprintf( stderr, "Crack aborted.\n" );
    return EXIT_FAILURE; 

  // checking for correct number of arguments
  } else if( ( ( args & S_FLAG ) && argc != S_ARG_NUM ) ||
  ( ( args == 0 ) && argc != ARG_NUM ) ){
    fprintf( stderr, "Invalid number of arguments. Crack aborted.\n" );
    return EXIT_FAILURE;

  } else{

    if( args & A_FLAG ){
      START_CHAR = LETTER_START;
      END_CHAR = LETTER_END;
    }else{
      START_CHAR = START;
      END_CHAR = END;
    }
    
    // Passwords generated, set in nextPass, is initalized as START_CHAR
    struct passwordInfo nextPass;
    nextPass.passwordLength = 1;
    nextPass.password = malloc(sizeof(char));
    nextPass.password[0] = START_CHAR;

    // checking if file to decrypt is a valid gpg encrypted file
    char * terminated;
    if( !validFileCheck( terminated = terminatePassword( nextPass.password,
    nextPass.passwordLength), argv[argc-1] ) ){
      free( terminated);
      fprintf( stderr, "File open error. Crack aborted.\n" );
      return EXIT_FAILURE;
    }

    if( args & S_FLAG ){
      printf("\nCracking...\n");
      printf("\n%s ", terminated);
    }else{
      printf("\nCracking");
      fflush(stdout);
    }

    free( terminated );

    int attempts = 1;
    
    // allows for '.' char to be printed out at a regular, DOTRATE
    // seconds interval.
    time_t dotTimekeeper;
    time_t dotCurrentTime;
    time( &dotTimekeeper );

    // repeadly calling passGen, trying new passwords until valid one is found
    
    while ( !attemptInput( terminated = terminatePassword( nextPass.password,
    nextPass.passwordLength ), argv[argc-1] ) ){

      nextPass = passGen( nextPass );

      // either prints a dot at a regular interval, or the password
      // attempted depending on flag
      if( args & S_FLAG ){
        printf("%s ", terminated);
      }else{
        time( &dotCurrentTime );

        if( (int) ( dotCurrentTime - dotTimekeeper ) >= DOT_RATE ){
          time( &dotTimekeeper );
          printf(".");
          fflush(stdout);
        }
      }

      free(terminated);
      attempts++;
    }

    free(terminated);
    
    // calculating time taken to crack and printing results
    clock_gettime( CLOCK_MONOTONIC, &endTime);

    float diffTime = (endTime.tv_sec - startTime.tv_sec) +
    ( ((float)(endTime.tv_nsec - startTime.tv_nsec)) / ((float)NANOSECOND) );

    printf( "\n\n *** PASSWORD FOUND: %s *** \n", terminated =
    terminatePassword( nextPass.password, nextPass.passwordLength ) );

    printf( " *** Cracked In: %f seconds, after %d attempts ***\n",
    diffTime, attempts );

    free(nextPass.password);
    free(terminated);

    return EXIT_SUCCESS;
  }
 
}
