#include "declaration.h"

Declaration::Declaration( const Type & type, const std::string & name ) :
  d_type( &type ),
  d_name( name )
{
}

const std::string & Declaration::getName() const { return d_name; }
