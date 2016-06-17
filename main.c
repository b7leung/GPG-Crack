#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "crackConstants.h"

int main( int argc, char * argv[] ){
  
  time_t startTime;
  time_t endTime;
  int args = parseArgs(argc, argv);
  
  // checking if there were any invalid flags
  if( args & ERR_FLAG ){
    fprintf( stderr, "Crack aborted." );
    return EXIT_FAILURE; 

  // checking if the number of arguments is correct
  } else if( ( ( args & S_FLAG ) && argc != S_ARG_NUM ) ||
  ( ( args == 0 ) && argc != ARG_NUM ) ){
    fprintf( stderr, "Invalid number of arguments. Crack aborted." );
    return EXIT_FAILURE;

  // performing crack
  } else{

    printf("\nCracking...\n");
    time( &startTime );
    
    // initalizes nextPass as START_CHAR 
    char * nextPass = malloc(sizeof(char));
    nextPass[0] = START_CHAR;
    char * terminated;

    // checking if file to decrypt is valid
    if( !validFileCheck( terminated = terminatePassword( nextPass ), argv[argc-1] ) ){
      free( terminated);
      fprintf( stderr, "File open error. Crack aborted.\n" );
      return EXIT_FAILURE;
    }
    free( terminated);

    if( args & S_FLAG ){
      printf("\n");
      printPassword( nextPass );
    }

    int attempts = 1;

    // repeadly calling passGen, trying new passwords until valid one is found
    while ( !attemptInput( terminated = terminatePassword( nextPass ), argv[argc-1] ) ){
      free(terminated);
      nextPass = passGen( nextPass );
      if( args & S_FLAG ){
        printPassword( nextPass );
      }
      attempts++;
    }

    if( args & S_FLAG ){
      printf("\n");
    }

    time( &endTime ); 

    printf("\n *** PASSWORD FOUND: %s *** \n", terminatePassword(nextPass));
    printf(" *** Cracked In: %d seconds, after %d attempts ***\n", endTime-startTime, attempts);

    system( "rm decrypt_output" );

    return EXIT_SUCCESS;
  }
  
}
