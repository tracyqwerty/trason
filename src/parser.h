#ifndef PARSOR_H
#define PARSOR_H
#include "json_element.h"
#include <iostream>
#include <string>

class Parser {
public:
  Parser(const std::string &source) : source_(source), i_(0) {}
  JsonElement *parse() { return parseValue(); }

private:
  void skipSpace();
  bool checkError(char c);
  JsonElement *parseArray();
  JsonElement *parseString();
  JsonElement *parseBoolean();
  JsonElement *parseNumber();
  JsonElement *parseObject();
  JsonElement *parseValue();
  JsonElement *parseNull();
  
  int i_;
  std::string source_;
};

#endif // PARSOR_H