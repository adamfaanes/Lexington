#ifndef PARSEABLE_H
#define PARSEABLE_H

#include <sstream>
#include <string>
#include <string.h>
#include <iostream>
#include <ctype.h>
#include <stdlib.h>

#include "parsenode.h"

enum PARSE_RETURN_CODES
{
  PARSE_NORMAL,
  PARSE_ENDWORD,
  PARSE_TRYAGAIN,
  PARSE_EOF
};


class Parseable : public ParseNode
{
  std::ostringstream m_token;
  int m_type;

  public:
  Parseable( );

  inline int getType() const
  {
    return m_type;
  }

  inline
  std::string str() const
  {
    return m_token.str();
  }

  void print() const;

  /**
   * Tests whether or not this parseable - if the given character were to be
   * appended to it - would remain a semantically unique structure. For
   * instance, "!" + "=" is meaningful, but "!" + "&" is not.
   */
  bool testLexical( char ch );

  int handleCharacter( int c );
};

#endif
