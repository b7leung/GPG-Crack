
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crackConstants.h"

// terminates password by appending char * with null char

char * terminatePassword( char * passwordGuess, int guessLength){

  char *terminatedPassword = malloc( guessLength + sizeof(char));
  // copying passwordGuess into bigger array
  int i;
  for( i = 0; i < guessLength; i++ ){
  //for( i = 0; i < 1; i++ ){
    terminatedPassword[i] = passwordGuess[i];
  }
  terminatedPassword[guessLength] = '\0';
  
  return terminatedPassword;
}

