#include "statement.h"
#include <iostream>
#include <stdexcept>
#include "compilation.h"

Statement::~Statement()
{
  for( NodeVectorIterator itr = m_nodes.begin();
       itr != m_nodes.end();
       itr++ )
  {
    delete *itr;
  }
}

int Statement::handleToken( Parseable * token )
{
  //std::cout << "Adding token " << token->str() << " to statement ";
  //print();
  if( token->str() == ";" )
    return STATEMENT_COMPLETE;
  m_nodes.push_back( token );
  return STATEMENT_NORMAL;
}

void Statement::print() const
{
  for( NodeVectorConstIterator itr = m_nodes.begin();
       itr != m_nodes.end();
       itr++ )
  {
    (*itr)->print();
    std::cout << " ";
  }
  std::cout << std::endl;
}

void Statement::encode( std::ostream & os, Scope & enclosingScope, const Scope & naturalScope )
{
  NodeVectorIterator itr = m_nodes.begin();
  if( (*itr)->str() == "print" )
  {
    os << "fprintf( ";
    itr++;
    for( ; itr != m_nodes.end(); itr++ )
    {
      os << (*itr)->str() << " ";
    }
    os << ");\n";
  }
  else if( (*itr)->str() == "include" )
  {
    std::ostringstream path;
    itr++;
    for( ; itr != m_nodes.end(); itr++ )
    {
      if( (*itr)->str() == "." )
        path << "/";
      else if( (*itr)->getType() == PARSE_IDENTIFIER ) 
        path << (*itr)->str();
      else
        throw std::runtime_error("Badly formed expression.");
    }
    path << ".mnh";
    //std::cout << path.str() << std::endl;
    Compilation inclusion( path.str().c_str(), naturalScope );
    enclosingScope.addScope( inclusion.getScope() );
  }
  else if( (*itr)->str() == "cdecl" )
  {
    print();
  }
}
