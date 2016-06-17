
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crackConstants.h"

// properly prints out password by appending char * with null char

void printPassword( char * passwordGuess ){

  char *printedPassword = malloc(sizeof(passwordGuess) + sizeof(char));
  strcpy(printedPassword, passwordGuess);
  printedPassword[strlen(passwordGuess)] = '\0';
  printf("%s ", printedPassword);
  free(printedPassword);
}

