#include "nativetype.h"

NativeType::NativeType( const std::string & name ) :
  d_name( name )
{
}

const std::string & NativeType::getName() const
{
  return d_name;
}
