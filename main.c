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

  //checking for help flag
  if( args & H_FLAG ){
    fprintf(stdout, USAGE);
    return EXIT_SUCCESS;

  // checking for invalid flags
  }else if( args & ERR_FLAG ){
    fprintf( stderr, ARGERROR);
    return EXIT_FAILURE; 

  // checking for correct number of arguments
  } else if( ( ( args & S_FLAG ) && argc != S_ARG_NUM ) ||
  ( ( args == 0 ) && argc != ARG_NUM ) ){
    fprintf( stderr, ARGERROR );
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
    char * password = malloc(2*sizeof(char));
    password[0] = START_CHAR;
    password[1] = '\0';

    // checking if file to decrypt is a valid gpg encrypted file
    if( !validFileCheck( password, argv[argc-1] ) ){
      fprintf( stderr, "File open error. Crack aborted.\n" );
      return EXIT_FAILURE;
    }

    if( args & S_FLAG ){
      printf("\nCracking...\n");
      printf("\n%s ", password);
    }else{
      printf("\nCracking");
      fflush(stdout);
    }

    int attempts = 1;
    
    // allows for '.' char to be printed out at a regular, DOTRATE
    // seconds interval.
    time_t dotTimekeeper;
    time_t dotCurrentTime;
    time( &dotTimekeeper );

    // repeadly calling passGen, trying new passwords until valid one is found
    
    while ( !attemptInput( password, argv[argc-1] ) ){

      password = passGen( password );

      // either prints the password attempted or a dot at a regular interval,
      // depending on flag
     
      if( args & S_FLAG ){
        printf("%s ", password);
      }else{
        time( &dotCurrentTime );
        if( (int) ( dotCurrentTime - dotTimekeeper ) >= DOT_RATE ){
          time( &dotTimekeeper );
          printf(".");
          fflush(stdout);
        }
      }
      attempts++;
    }
    
    // calculating time taken to crack and printing results
    clock_gettime( CLOCK_MONOTONIC, &endTime);
    float diffTime = (endTime.tv_sec - startTime.tv_sec) +
    ( ((float)(endTime.tv_nsec - startTime.tv_nsec)) / ((float)NANOSECOND) );

    printf( "\n\n *** PASSWORD FOUND: %s *** \n", password);
    printf( " *** Cracked In: %f seconds, after %d attempts *** \n",
    diffTime, attempts );

    free(password);
    return EXIT_SUCCESS;
  }
 
}
