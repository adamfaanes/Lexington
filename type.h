#ifndef TYPE_H
#define TYPE_H

#include "identifier.h"

class Type : public Identifier
{
  public:
    virtual const std::string & getName() const = 0;
};

#endif
