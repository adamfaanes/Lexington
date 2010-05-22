#ifndef STATEMENT_H
#define STATEMENT_H

#include <vector>
#include "parsenode.h"
#include "parseable.h"
#include "scope.h"

enum
{
  STATEMENT_NORMAL,
  STATEMENT_COMPLETE
};

class Statement //: public ParseNode
{
  private:
    typedef std::vector<ParseNode*> NodeVector;
    typedef NodeVector::iterator NodeVectorIterator;
    typedef NodeVector::const_iterator NodeVectorConstIterator;

    NodeVector m_nodes;
  public:
    ~Statement();
    int handleToken( Parseable * token );
    virtual void print() const;
    std::string str() const
    {
      return std::string();
    }
    void encode( std::ostream & os, Scope & enclosingScope, const Scope & naturalScope );
};

#endif
