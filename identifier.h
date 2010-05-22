#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>

class Identifier
{
  public:
    virtual const std::string & getName() const = 0;
};

#endif
