
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crackConstants.h"

// guesses password up to specified maxPassLength by brute force.
// given the last Password Attempt, will return the next Password Attempt
char * passGen(char * lastPassAttempt){

  //char initialGuess = START_CHAR;
  //char * passwordGuess = malloc(sizeof(char));
  char * passwordGuess = lastPassAttempt;
  //printf("%c\n", *passwordGuess);
  //printPassword(passwordGuess);
  //passwordGuess[0] = initialGuess;
  //int counter = 0;
  
  //while( ( strlen(passwordGuess) <= maxPassLength ) &&
  //while( !( ( strlen(passwordGuess) == maxPassLength ) && full(passwordGuess) ) ){
    
   /* if(counter%1000000 == 0 ){
      printPassword( passwordGuess );
    }*/

    // if the first letter is not z, keep on incrementing
    if( passwordGuess[0] != END_CHAR ){

      passwordGuess[0]++;

    }else{

      // String becomes larger by 1 and 'a'-filled if string was filled with 'z's. 
      if(full(passwordGuess)){
        char * passBuffer = malloc(sizeof(passwordGuess) + sizeof(char));
        aFill( passBuffer, strlen(passwordGuess)+1 ); 
        free(passwordGuess);
        passwordGuess = passBuffer;

      }else{
      // If string not filled with 'z's, increment the biggest possible non-z char
      // and reset the previous chars to 'a's
        
        int biggestCharIndex = 1;
        while( passwordGuess[biggestCharIndex] == END_CHAR ){
          biggestCharIndex++;
        }
        passwordGuess[biggestCharIndex]++;
        aFill( passwordGuess, biggestCharIndex );

      }
  
    }  
    //counter++;
  //}

  //printPassword( passwordGuess );
  //printf("***\n");
  return passwordGuess;
}



