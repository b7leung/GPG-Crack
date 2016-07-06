#ifndef CRACK_CONSTANT_H
#define CRACK_CONSTANT_H

// flags 
#define CHAR_S_FLAG 's'
#define CHAR_S_LONG "show_attempts"
#define S_FLAG 0x1
#define OPTSTRING "hsa"

#define CHAR_A_FLAG 'a'
#define CHAR_A_LONG "alphabetic"
#define A_FLAG 0x2

#define CHAR_H_FLAG 'h'
#define CHAR_H_LONG "help"
#define H_FLAG 0x4

#define ERR_FLAG 0x8

// global constants
#define DECRYPT_COMMAND_1 "gpg --passphrase \""
#define DECRYPT_COMMAND_2 "\" -d "
#define DECRYPT_COMMAND_3 " 2> decrypt_output 1> /dev/null"

#define ARG_NUM 2
#define S_ARG_NUM 3

extern char START_CHAR;
extern char END_CHAR;
#define LETTER_START 'a'
#define LETTER_END 'z'
#define START '_'
#define END '~'

#define SUCCESS_MSG_LINE_0 "gpg: CAST5 encrypted data"
#define SUCCESS_MSG_LINE_1 "gpg: encrypted with 1 passphrase"
#define SUCCESS_MSG_LINE_2 "gpg: WARNING: message was not integrity protected"
#define SUCCESS_MSG_LINES 3

#define NANOSECOND 1000000000
#define DOT_RATE 1

#define USAGE "USAGE: Crack decrypts symmetrically encrypted .gpg files with brute force.\
\n\nFlags:\
\n-a or -- alphabetic: Only attempt alphabetic passwords.\
\n-s or --show_attempts: Print out current attempt (Program will run slightly slower).\
\n-h or --help: Print out usage information.\n"

#define OPENERROR "FIle open error. Crack aborted. Use the --help flag for more information\n"
#define ARGERROR "Argument error. Crack aborted. Use the --help flag for more information\n"

// function prototypes
int full( char * passwordGuess );
char * terminatePassword( char * passwordGuess, int guessLength);
int attemptInput( char * password, char * filename);
int validFileCheck( char * password, char * filename);
int parseArgs( int argc, char * argv[] );
char * passGen( char * password );

#endif
