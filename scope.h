#ifndef SCOPE_H
#define SCOPE_H

#include "identifier.h"
#include <map>
#include <vector>

class Scope;

class ScopeInclusion
{
  private:
    const Scope * d_scope;
  public:
    ScopeInclusion( const Scope * scope );
    const Scope & operator* () const
    { return *d_scope; }
    const Scope * operator-> () const
    { return d_scope; }
};

class Scope
{
  public:
    Scope();
    Scope( const Scope & naturalScope );
    void addIdentifier( Identifier & value );
    bool hasIdentifier( const std::string & label ) const;
    const Identifier & getIdentifier( const std::string & label ) const;
    void addScope( const Scope & scope );
  private:
    typedef std::map<std::string, Identifier*> IdentifierMap;
    typedef IdentifierMap::iterator IdentifierMapIterator;
    typedef IdentifierMap::const_iterator IdentifierMapCItr;
    IdentifierMap d_identifiers;
    typedef std::vector<ScopeInclusion> ScopeInclusionVec;
    typedef ScopeInclusionVec::iterator ScopeInclusionVecItr;
    ScopeInclusionVec d_includedScopes;
};

#endif
