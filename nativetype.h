#ifndef NATIVETYPE_H
#define NATIVETYPE_H

#include "type.h"

class NativeType : public Type
{
  private:
    std::string d_name;
  public:
    NativeType( const std::string & name );
    const std::string & getName() const;
};
#endif
