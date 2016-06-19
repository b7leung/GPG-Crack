
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crackConstants.h"

// guesses password up to specified maxPassLength by brute force.
// given the last Password Attempt, will return the next Password Attempt

//char * passGen(char * lastPassAttempt){
struct passwordInfo passGen( struct passwordInfo password ){
  
  char * passwordGuess = password.password;
  char * terminated;
  // if the first letter is not z, keep on incrementing
  if( passwordGuess[0] != END_CHAR ){

    passwordGuess[0]++;

  }else{

    // String becomes larger by 1 and 'a'-filled if string was filled with 'z's. 
    if(full(terminated = terminatePassword(passwordGuess, password.passwordLength))){
      char * passBuffer = malloc(sizeof(passwordGuess) + sizeof(char));
      aFill( passBuffer, ++password.passwordLength ); 
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
      free(terminated);
  }  

  password.password = passwordGuess;

  return password;
}



