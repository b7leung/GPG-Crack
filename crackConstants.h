
#ifndef CRACKCONSTANT_H
#define CRACK_CONSTANT_H

#define START_CHAR 'a'
#define END_CHAR 'z'
#define DECRYPT_COMMAND_1 "gpg --passphrase \""
#define DECRYPT_COMMAND_2 "\" -d "
#define DECRYPT_COMMAND_3 " 2> decrypt_output 1> /dev/null"
#define CHAR_S_FLAG 's'
#define CHAR_S_LONG "show_attempts"
#define S_FLAG 0x1
#define ERR_FLAG 0x2
#define OPTSTRING "s"
#define ARG_NUM 2
#define S_ARG_NUM 3


void printPassword( char * passwordGuess );
char * passGen( char * password );
int full( char * passwordGuess );
void aFill( char * password, int fillAmt);
char * terminatePassword( char * passwordGuess );
int attemptInput( char * password, char * filename);
int validFileCheck( char * password, char * filename);
int parseArgs( int argc, char * argv[] );

#endif
