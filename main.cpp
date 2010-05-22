#define DEBUG_STATEMENT_BUILDER

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "compilation.h"
#include "nativetype.h"

int main()
{
  //printf("starting...\n");

  Scope naturalScope;

  NativeType VOID( "void" );
  NativeType STRING( "str" );

  naturalScope.addIdentifier( VOID );
  naturalScope.addIdentifier( STRING );

  try
  {
    Compilation compilation( "main.mnh", naturalScope );
  }
  catch( const std::runtime_error & exception )
  {
    std::cerr << "Runtime error: " << exception.what();
    return EXIT_FAILURE;
  }
  catch( ... )
  {
    std::cerr << "Unknown error " << std::endl;
    return EXIT_FAILURE;
  }
  //printf( "Exiting..." );
  return EXIT_SUCCESS;
}
