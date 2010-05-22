#include "parseable.h"
#include <stdexcept>


static const char lexical[] = "~!%^&*()-=+{}[]|:;\"'<,>./?";

static const char * lexMultiChars[] =
{
  "~",
  "!",
  "%",
  "^",
  "&",
  "*",
  "(",
  ")",
  "-",
  "=",
  "+",
  "{",
  "}",
  "[",
  "]",
  "/",
  ":",
  ";",
  "\"",
  "'",
  "<",
  ",",
  ">",
  ".",
  "/",
  "?",
  "~=",
  "!=",
  "%=",
  "^=",
  "&=",
  "*=",
  "-=",
  "+=",
  "/=",
  "<=",
  ">=",
  "==",
  "->",
  "++",
  "--",
  "<<",
  ">>",
  "<<=",
  ">>=",
  "::"
};

bool isLexicalStat( char ch )
{
  for ( int i = 0; i < sizeof( lexical ) - 1; i++ )
  {
    if( lexical[i] == ch )
      return true;
  }
  return false;
}

Parseable::Parseable( ) :
  m_type( PARSE_EMPTY )
{
}

bool Parseable::testLexical( char ch )
{
  std::string test = m_token.str();
  test += ch;
  const char * ctest = test.c_str();
  for( int i = 0; i < sizeof( lexMultiChars ) / sizeof( char* ); i++ )
  {
    //std::cout << "a: " << lexMultiChars[i] << ", b: " << ctest << ", c: " << test.size() << std::endl;
    // ...yes, memcmp.
    if( !memcmp( lexMultiChars[i], ctest, test.size() ) )
      return true;
  }
  return false;
}

int Parseable::handleCharacter( int i )
{
  char c = static_cast<char>( i );
  //std::cout << "Adding character " << c << " to " << m_token.str() << std::endl;
  if( c == EOF )
    return PARSE_EOF;
  switch( getType() )
  {
    case PARSE_EMPTY:

      /* The token is presently empty, so we need to identify what it is */

      // Consume all whitespace
      
      if( isspace( c ) )
        return PARSE_NORMAL;

      // If the first character is ", it's a string.
      
      if( c == '"' )
      {
        m_type = PARSE_STRING;
        return PARSE_NORMAL;
      }

      // If it's a lexical character, the token is lexical.
      
      if( isLexicalStat( c ) )
      {
        m_type = PARSE_LEXICAL;
        m_token << c;
        return PARSE_NORMAL;
      }

      // If it's anything else, it must be an identifier.

      m_token << c;
      m_type = PARSE_IDENTIFIER;
      return PARSE_NORMAL;
      break;
    case PARSE_STRING:
      if( c == '"' )
        return PARSE_ENDWORD;
      else
      {
        m_token << c;
        return PARSE_NORMAL;
      }

      break;

    case PARSE_LEXICAL:
      if( isspace( c ) )
        return PARSE_ENDWORD;
      if( testLexical( c ) )
      {
        m_token << c;
        return PARSE_NORMAL;
      }
      else
        return PARSE_TRYAGAIN;

      break;

    case PARSE_IDENTIFIER:
      if( isspace( c ) )
        return PARSE_ENDWORD;
      if( isLexicalStat( c ) )
        return PARSE_TRYAGAIN;
      m_token << c;
      break;

    default:
      throw std::runtime_error("Unknown argument type.");
      return PARSE_NORMAL;
  }
}

void Parseable::print() const
{
  std::cout << m_token.str();
}
