#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "crackConstants.h"

/*
 * Method Name: parseArgs
 * Description: Parses arguments for Crack
 * Parameter(s): 
 *   > int argc -- number of arguments
 *   > char * argv[] --  array of arguments passed in
 * Side Effect(s): None
 * Return: int with appropriate flags ORed 
 */

int parseArgs( int argc, char * argv[] ){
  
  int getopt_result;
  int optionindex;
  int args = 0;

  static struct option long_options[] =
  {
    { CHAR_S_LONG, no_argument, NULL, CHAR_S_FLAG },
    { CHAR_A_LONG, no_argument, NULL, CHAR_A_FLAG },
    { 0, 0, 0, 0}
  };

  // continues scanning arguments until there aren't any left,
  // flagging the appropriate bits for the corresponding flag
  while( ( getopt_result = getopt_long( argc, argv, OPTSTRING,
  long_options, &optionindex) )!= -1 ){

    switch(getopt_result){

      case CHAR_S_FLAG:
        args = args | S_FLAG;
        break;

      case CHAR_A_FLAG:
        args = args | A_FLAG;
        break;

      case '?':
        args = args | ERR_FLAG;
        break;
      
      case ':':
        args = args | ERR_FLAG;
        break;
    }

  }

  return args;

}
