#include "compilation.h"
#include <stdexcept>
#include <fstream>

void Compilation::handleWord()
{
  /* There's nothing to do if the token is currently empty. */
  //if( m_word == NULL || m_word->str().size() == 0 )
  //  return;
  // std::cout << m_word->str() << std::endl;
  m_tokens.push_back( m_word );
  m_word = new Parseable();
}

void Compilation::parseTokens( FILE * pFile )
{
  m_word = new Parseable();

  while( true )
  {
    /* Extract the words. */
    int c = fgetc( pFile );
    int rcode = m_word->handleCharacter( c );
    
    switch( rcode )
    {
      case PARSE_NORMAL:
        break;
      case PARSE_ENDWORD:
        handleWord();
        break;
      case PARSE_TRYAGAIN:
        handleWord();
        m_word->handleCharacter( c );
        break;
      case PARSE_EOF:
        handleWord();
        return;
    };
  }

}

Compilation::Compilation( const char * filename, const Scope & naturalScope ) :
  m_scope( naturalScope )
{
  FILE* pFile = fopen( filename, "r" );
  std::ofstream os( "compile.c" );

  /* Check if the file was successfully loaded */

  if( pFile == NULL )
  {
    std::ostringstream str;
    str << "ERROR: Could not open file " << filename << std::endl;
    throw std::runtime_error( str.str() );
  }

  // Parse tokens

  parseTokens( pFile );
  
  // Handle statements

  m_statement = new Statement();
  
  for( TokenVectorIterator itr = m_tokens.begin();
      itr != m_tokens.end();
      itr++ )
  {
    int rcode = m_statement->handleToken( *itr );
    switch( rcode )
    {
      case STATEMENT_NORMAL:
        break;
      case STATEMENT_COMPLETE:
        //std::cerr << "handling statement" << std::endl;
        handleStatement();
        break;
    }
  }

  // Print statements
  os << "int main()\n{\n";
  for( StatementVectorIterator itr = m_statements.begin();
       itr != m_statements.end();
       itr++ )
  {
    os << "   ";
    (*itr)->encode( os, m_scope, naturalScope );
  }
  os << "}" << std::endl;
}

Compilation::~Compilation()
{
  // TODO: destroy all the stuff the vectors point to.
}

void Compilation::handleStatement()
{
  m_statement->print();
  m_statements.push_back( m_statement );
  m_statement = new Statement();
}
