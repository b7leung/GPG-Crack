#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crackConstants.h"

/*
 * Method Name: terminatePassword
 * Description: terminates password by appending char * with null char
 * Parameter(s):
 *   > char * passwordGuess -- array of chars to null terminate
 *   > int guessLength -- length of array of chars
 * Side Effect(s): terminated char is malloc'd
 * Return: terminated string
 */

char * terminatePassword( char * passwordGuess, int guessLength){

  char *terminatedPassword = malloc( guessLength + sizeof(char));
  // copying passwordGuess into bigger array

  int i;
  for( i = 0; i < guessLength; i++ ){
    terminatedPassword[i] = passwordGuess[i];
  }
  terminatedPassword[guessLength] = '\0';
  
  return terminatedPassword;
}

