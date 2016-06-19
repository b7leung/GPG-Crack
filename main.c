#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "crackConstants.h"

char START_CHAR;
char END_CHAR;

int main( int argc, char * argv[] ){

  struct timespec startTime;
  struct timespec endTime;
  clock_gettime( CLOCK_MONOTONIC, &startTime);

  int args = parseArgs(argc, argv);
  
  // checking if there were any invalid flags
  if( args & ERR_FLAG ){
    fprintf( stderr, "Crack aborted.\n" );
    return EXIT_FAILURE; 

  // checking if the number of arguments is correct
  } else if( ( ( args & S_FLAG ) && argc != S_ARG_NUM ) ||
  ( ( args == 0 ) && argc != ARG_NUM ) ){
    fprintf( stderr, "Invalid number of arguments. Crack aborted.\n" );
    return EXIT_FAILURE;

  // performing crack
  } else{

    if( args & A_FLAG ){
      START_CHAR = LETTER_START;
      END_CHAR = LETTER_END;
    }else{
      START_CHAR = START;
      END_CHAR = END;
    }
    
    // initalizes nextPass as START_CHAR 
    struct passwordInfo nextPass;
    nextPass.passwordLength = 1;
    nextPass.password = malloc(sizeof(char));
    nextPass.password[0] = START_CHAR;
    char * terminated;

    // checking if file to decrypt is valid
    if( !validFileCheck( terminated = terminatePassword( nextPass.password, nextPass.passwordLength), argv[argc-1] ) ){
      free( terminated);
      fprintf( stderr, "File open error. Crack aborted.\n" );
      return EXIT_FAILURE;
    }

    if( args & S_FLAG ){
      printf("\nCracking...\n");
    }else{
      printf("\nCracking");
      fflush(stdout);
    }


    if( args & S_FLAG ){
      printf("\n%s ", terminated);
    }

    free( terminated );

    int attempts = 1;

    time_t dotTimekeeper;
    time_t dotCurrentTime;
    time( &dotTimekeeper );

    // repeadly calling passGen, trying new passwords until valid one is found
    while ( !attemptInput( terminated = terminatePassword( nextPass.password, nextPass.passwordLength ), argv[argc-1] ) ){
      nextPass = passGen( nextPass );
      if( args & S_FLAG ){
        printf("%s ", terminated);
      }else{
        time( &dotCurrentTime );
        if( (int) ( dotCurrentTime - dotTimekeeper ) >= 1 ){
          time( &dotTimekeeper );
          printf(".");
          fflush(stdout);
        }
      }
      free(terminated);
      attempts++;
    }

    free(terminated);

    if( args & S_FLAG ){
      printf("\n");
    }

    clock_gettime( CLOCK_MONOTONIC, &endTime);
    float diffTime = (endTime.tv_sec - startTime.tv_sec) + ( ((float)(endTime.tv_nsec - startTime.tv_nsec)) / ((float)NANOSECOND) );

    printf("\n\n *** PASSWORD FOUND: %s *** \n", terminated = terminatePassword( nextPass.password, nextPass.passwordLength ));
    printf(" *** Cracked In: %f seconds, after %d attempts ***\n", diffTime,
    //printf(" *** Cracked In: %f seconds, after %d attempts ***\n", diffTime( startTime.tv_nsec, endTime.tv_nsec ),
    attempts);

    //system( "rm decrypt_output" );
    free(nextPass.password);
    free(terminated);

    return EXIT_SUCCESS;
  }
 
}
