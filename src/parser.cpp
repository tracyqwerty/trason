#include "parser.h"

void Parser::skipSpace() {
  // Warning: can ':' and ',' be skipped? --Yes!
  while (source_[i_] == ' ' || source_[i_] == '\n' || source_[i_] == '\t' ||
         source_[i_] == ':' || source_[i_] == ',') {
    i_++;
  }
}

bool Parser::checkError(char c) {
  if (source_[i_] != c) {
    std::cout << "error for " << c << std::endl;
    return false;
  }
  return true;
}

JsonElement *Parser::parseArray() {
  skipSpace();
  if (!checkError('[')) {
    return nullptr;
  } else {
    i_++;
  }

  JsonElement *json_element =
      new JsonElement(JsonElement::Type::ARRAY, JsonElement::JsonArray());

  while (source_[i_] != ']') {
    auto value = parseValue();
    std::get<JsonElement::JsonArray>(json_element->value_).emplace_back(value);
    skipSpace();
  }
  i_++;

  return json_element;
}

JsonElement *Parser::parseString() {
  std::string str = "";
  skipSpace();
  if (!checkError('"')) {
    return nullptr;
  } else {
    i_++;
  }
  while (source_[i_] != '"') {
    str += source_[i_];
    i_++;
  }
  i_++;
  return new JsonElement(JsonElement::Type::STRING, str);
}

JsonElement *Parser::parseBoolean() {
  skipSpace();
  std::string str;
  str += source_[i_++];
  while (source_[i_] >= 'a' && source_[i_] <= 'z') {
    str += source_[i_];
    i_++;
  }
  if (str == "true" || str == "True") {
    return new JsonElement(JsonElement::Type::BOOLEAN, true);
  } else if (str == "false" || str == "False") {
    return new JsonElement(JsonElement::Type::BOOLEAN, false);
  } else {
    std::cout << "bad input" << std::endl;
    return nullptr;
  }
}

JsonElement *Parser::parseNull() {
  skipSpace();
  std::string str;
  str += source_[i_++];
  while (source_[i_] >= 'a' && source_[i_] <= 'z') {
    str += source_[i_];
    i_++;
  }
  if (str == "null" || str == "NULL") {
    return new JsonElement(JsonElement::Type::NULL_VALUE, false);
  } else {
    std::cout << "bad input" << std::endl;
    return nullptr;
  }
}

JsonElement *Parser::parseNumber() {
  skipSpace();
  std::string num = "";
  int f = 1;
  if (source_[i_] == '-') {
    f = -1;
    i_++;
  }
  while (source_[i_] == '.' || (source_[i_] >= '0' && source_[i_] <= '9')) {
    num += source_[i_];
    i_++;
  }
  return new JsonElement(JsonElement::Type::NUMBER, std::stod(num) * f);
}

JsonElement *Parser::parseObject() {
  skipSpace();
  if (!checkError('{')) {
    return nullptr;
  } else {
    i_++;
  }

  JsonElement *json_element =
      new JsonElement(JsonElement::Type::OBJECT, JsonElement::JsonObject());

  while (source_[i_] != '}') {
    auto key = std::get<std::string>(parseString()->value_);
    // std::cout << "key is:" << key;
    auto value = parseValue();
    // std::cout << std::get<std::string>(value->value_) << std::endl;
    // std::cout << std::get<bool>(value->value_) << std::endl;
    std::get<JsonElement::JsonObject>(json_element->value_)[key] = value;
    skipSpace();
  }
  i_++;

  return json_element;
}

JsonElement *Parser::parseValue() {
  skipSpace();
  switch (source_[i_]) {
  case '{':
    return parseObject();
  case '[':
    return parseArray();
  case '"':
    return parseString();
  // use multiple case values without using a break between them.
  case 't':
  case 'T':
  case 'f':
  case 'F':
    return parseBoolean();
  case 'n':
  case 'N':
    return parseNull();
  default:
    return parseNumber();
  }
  return nullptr;
}