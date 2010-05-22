#ifndef CDECL_H
#define CDECL_H

#include <vector>
#include <string>
#include "type.h"
#include "declaration.h"

class CDeclaration
{
  private:
    const Type * d_returnType;
    std::string d_name;
    std::vector< Declaration > d_arguments;
    std::string d_cname;
    std::string d_cheader;
  public:
    CDeclaration( const Type & ret,
        const std::string & name, 
        const std::string & cname, 
        const std::string & cheader );
    void addArgument( const Declaration & decl );
};

#endif
