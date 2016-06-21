#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "crackConstants.h"


//checks if all of the letters in a string are equal to END_CHAR, or "full"
// 0 for false, 1 for true

/*
 * Method Name: full
 * Description: Checks if all the letters in a given string are equal to
 * END_CHAR (if it is, then the string is "full").
 * Parameter(s): 
 *   > char * passwordGuess -- String to check
 * Side Effect(s): none
 * Return: 1 if all the letters in the string are equal to END_CHAR, 0
 * otherwise.
 */

int full( char * passwordGuess ){
  
  int full = 1;

  unsigned int i;

  for( i = 0; i < strlen(passwordGuess); i++){

    if(passwordGuess[i]!= END_CHAR){
      full = 0;
      break;
    }

  }

  return full;
}

