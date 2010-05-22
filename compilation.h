#ifndef COMPILATION_H
#define COMPILATION_H

#include <vector>
#include "parseable.h"
#include "statement.h"
#include "scope.h"

class Compilation
{
  private:
    typedef std::vector< Parseable * > TokenVector;
    typedef TokenVector::iterator TokenVectorIterator;
    typedef std::vector< Statement * > StatementVector;
    typedef StatementVector::iterator StatementVectorIterator;
    std::vector< Parseable* > m_tokens;
    std::vector< Statement* > m_statements;
    Scope m_scope;

    Parseable * m_word;
    Statement * m_statement;

    void handleWord();
    void handleStatement();
    void parseTokens( FILE * pFile );
  public:
    Compilation( const char * filename, const Scope & scope );
    inline const Scope & getScope() const
    { return m_scope; }
    ~Compilation();
};
#endif
