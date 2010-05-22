#ifndef DECLARATION_H
#define DECLARATION_H

#include "identifier.h"
#include "type.h"

class Declaration : public Identifier
{
  private:
    const Type * d_type;
    std::string d_name;
  public:
    Declaration( const Type & type, const std::string & name );
    inline const Type & getType() const { return *d_type; }
    const std::string & getName() const;
};

#endif
