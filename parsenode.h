#ifndef PARSENODE_H
#define PARSENODE_H

enum PARSE_TYPES
{
  PARSE_EMPTY,
  PARSE_IDENTIFIER,
  PARSE_STRING,
  PARSE_LEXICAL
};

class ParseNode
{
  public:
    virtual void print() const = 0;
    virtual std::string str() const = 0;
    virtual int getType() const = 0;
};
#endif
