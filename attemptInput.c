
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crackConstants.h"

// returns 1 if password worked; 0 if it didn't
int attemptInput( char * password, char * filename ){
  
  int passwordValid = 1;

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
  

  // looking at output of attempt to see if password was valid
  FILE * decrypt_output = fopen( "decrypt_output", "r");
  char outputLine[BUFSIZ]; 
  
  int lineNum = 0;
  while( fgets( outputLine, BUFSIZ, decrypt_output ) != NULL ){

    //printf("Output line %d: %s\n", lineNum, outputLine); 

    if( ( lineNum == 0 && strstr( outputLine, SUCCESS_MSG_LINE_0 ) == NULL ) ||
    ( lineNum == 1 && strstr( outputLine, SUCCESS_MSG_LINE_1 ) == NULL ) ||
    ( lineNum == 2 && strstr( outputLine, SUCCESS_MSG_LINE_2 ) == NULL ) ){
      passwordValid = 0;
      break;
    }
    lineNum++;
  }

  if( lineNum != ( SUCCESS_MSG_LINES  ) ){
    passwordValid = 0;
  }
      
  free(decryptCommand);
  fclose( decrypt_output );

  return passwordValid;
}

