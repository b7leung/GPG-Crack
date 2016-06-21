#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crackConstants.h"

/*
 * Method Name: validFileCheck
 * Description: Checks if given file is a valid symmetrically encrypted
 * gpg file.
 * Parameter(s): File & length of file.
 * Side Effect(s): none
 * Return: 1 if it's valid, 0 if it's not valid.
 */

int validFileCheck( char * password, char * filename ){
  
  int fileValid = 1;

  // assembling console command to call
  char * decryptCommand = malloc( sizeof(filename) + sizeof(DECRYPT_COMMAND_1)
  + sizeof(DECRYPT_COMMAND_2) + sizeof(DECRYPT_COMMAND_3) + sizeof(password) );
  strcpy( decryptCommand, DECRYPT_COMMAND_1 );
  strcat( decryptCommand, password );
  strcat( decryptCommand, DECRYPT_COMMAND_2 );
  strcat( decryptCommand, filename);
  strcat( decryptCommand, DECRYPT_COMMAND_3 );
  
  // calls command and attempts to decrypt with given password on file;
  // output of attempt is redirected to decrypt_output.
  system(decryptCommand);
  

  // looking at output of attempt to see if file was valid
  FILE * decrypt_output = fopen( "decrypt_output", "r");
  char outputLine[BUFSIZ]; 

  while( fgets( outputLine, BUFSIZ, decrypt_output ) != NULL ){
    if( strstr( outputLine, "file open error" ) != NULL ){
      fileValid = 0;
      break;
    }
  }
      
  free(decryptCommand);
  fclose( decrypt_output );
  return fileValid;
}

