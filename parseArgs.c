#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "crackConstants.h"

int parseArgs( int argc, char * argv[] ){
  
  int getopt_result;
  int optionindex;
  int args = 0;

  static struct option long_options[] =
  {
    { CHAR_S_LONG, no_argument, NULL, CHAR_S_FLAG },
    { 0, 0, 0, 0}
  };

  while( ( getopt_result = getopt_long( argc, argv, OPTSTRING, long_options, &optionindex) )!= -1 ){

    switch(getopt_result){

      case CHAR_S_FLAG:
        args = args | S_FLAG;
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
