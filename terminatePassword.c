
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crackConstants.h"

// terminates password by appending char * with null char

char * terminatePassword( char * passwordGuess ){

  char *terminatedPassword = malloc(sizeof(passwordGuess) + sizeof(char));
  strcpy(terminatedPassword, passwordGuess);
  terminatedPassword[strlen(passwordGuess)] = '\0';
  
  return terminatedPassword;
}

