#include "cdecl.h"

CDeclaration::CDeclaration( const Type & ret,
    const std::string & name, 
    const std::string & cname, 
    const std::string & cheader ) :
  d_returnType( &ret ),
  d_name( name ),
  d_cname( cname ),
  d_cheader( cheader )
{
}

void CDeclaration::addArgument( const Declaration & decl )
{
  d_arguments.push_back( decl );
}
