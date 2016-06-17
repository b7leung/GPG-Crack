
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crackConstants.h"
// fills string with specified fillAmt 'a' charachters,
// starting from index 0 of the char *

void aFill( char * password, int fillAmt){ 
  int i;
  for( i = 0; i < fillAmt; i++ ){
  
    password[i] = 'a';

  }
}
