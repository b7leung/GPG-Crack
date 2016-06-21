#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crackConstants.h"

/*
 * Method Name: aFill
 * Description: Fills given string with a specified amount of 
 * START_CHAR charachters. 
 * Parameter(s): 
 *  > char * password -- password to fill
 *  > int fillAmt -- how many START_CHARs to fill, starting from index 0
 * Side Effect(s): password is filled with START_CHAR
 * Return: none
 */

void aFill( char * password, int fillAmt){ 

  int i;

  for( i = 0; i < fillAmt; i++ ){
  
    password[i] = START_CHAR;

  }

}
