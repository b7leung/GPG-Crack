#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crackConstants.h"

/*
 * Method Name: attemptInput
 * Description: Attempts to decrypt given encrypted .gpg file with a given
 * password.
 * Parameter(s): 
 *   > char * password -- password to attempt
 *   > char * filename -- name of encrypted .gpg file
 * Side Effect(s): gpg is called using system-level commands and the password
 * is used to decrypt. Results are redirected to a file called decrypted_output
 * and it is analyzed to see if decryption was successful.
 * Return: 1 if the password worked; 0 otherwise.
 */

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
  
  // attempting to decrypt
  system(decryptCommand);

  // looking at stderr output of attempt to see if password was valid
  FILE * decrypt_output = fopen( "decrypt_output", "r");
  char outputLine[BUFSIZ]; 
  
  int lineNum = 0;
  while( fgets( outputLine, BUFSIZ, decrypt_output ) != NULL ){
    
    // if the stderr output doesn't match the correct message,
    // then password is invalid
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

