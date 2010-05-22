#include <sstream>
#include "scope.h"
#include <stdexcept>

ScopeInclusion::ScopeInclusion( const Scope * scope ) :
  d_scope( scope )
{
}

Scope::Scope()
{
}

Scope::Scope( const Scope & vec )
{
  ScopeInclusion inc( &vec );
  d_includedScopes.push_back( inc );
}

bool Scope::hasIdentifier( const std::string & label ) const
{
  return d_identifiers.find( label ) != d_identifiers.end();
}

void Scope::addIdentifier( Identifier & label )
{
  if( hasIdentifier( label.getName() ) )
  {
    std::ostringstream oss;
    oss << "Identifier " << label.getName() << " is being redeclared";
    throw std::runtime_error( oss.str() );
  }
  d_identifiers[label.getName()] = &label;
}

const Identifier & Scope::getIdentifier( const std::string & label ) const
{
  if( hasIdentifier( label ) )
  {
    IdentifierMapCItr itr = d_identifiers.find( label );
    return *itr->second;
  }
  for( int i = 0; i < d_includedScopes.size(); i++ )
  {
    if( d_includedScopes[i]->hasIdentifier( label ) )
    {
      return d_includedScopes[i]->getIdentifier( label );
    }
  }
  std::ostringstream oss;
  oss << "Identifier " << label << " is not defined in the current scope";
  throw std::runtime_error( oss.str() );
}

void Scope::addScope( const Scope & scope )
{
  ScopeInclusion inc( &scope );
  d_includedScopes.push_back( inc );
}
