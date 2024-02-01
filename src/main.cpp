#include "json_element.h"
#include "token.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// A raw string literal starts with R"( followed by a delimiter (which can be
// empty), the raw string content, the same delimiter, and finally )". The
// delimiter can be any sequence of characters and is used to allow the raw
// string to contain the sequence )" by ensuring it does not appear in the
// delimiter.

// Using raw string literals for JSON data in C++ code is particularly
// convenient because:
// 1. You don't have to escape double quotes ("), which are frequently used in
// JSON.
// 2. You can format the JSON content in a way that's easy to read, including
// newlines and indentation, without cluttering the string with escape
// sequences.
JsonElement *parseValue();
static auto source = R"(
{
    "hello": "world",
    "foo": 1.01,
    "urgent":    True,
    "expensive":    False,
}
)";

// "hello": "world",
// "foo" : 2.01,
// "urgent": true,
// "expensive" : False
// "foo": 1.0,
// "bar": true,
// "baz": null
static int i = 0;

void skipSpace() {
  // warning: can ':' and ',' be skipped?
  while (source[i] == ' ' || source[i] == '\n' || source[i] == '\t' ||
         source[i] == ':' || source[i] == ',') {
    i++;
  }
}

bool checkError(char c) {
  if (source[i] != c) {
    std::cout << "error for " << c << std::endl;
    return false;
  }
  return true;
}

void parseArray() {
  while (source[i] != ']') {
    // parseValue();
  }
  i++;
}

JsonElement *parseString() {
  std::string str = "";
  skipSpace();
  if (!checkError('"')) {
    return nullptr;
  } else {
    i++;
  }
  while (source[i] != '"') {
    str += source[i];
    i++;
  }
  i++;
  //   std::cout << str << std::endl;
  return new JsonElement(JsonElement::Type::STRING, str);
}

JsonElement *parseBoolean() {
  skipSpace();
  std::string str;
  str += source[i++];
  while (source[i] >= 'a' && source[i] <= 'z') {
    str += source[i];
    i++;
  }
  std::cout << str << std::endl;
  i++;
  if (str == "true" || str == "True") {
    return new JsonElement(JsonElement::Type::BOOLEAN, true);
  } else if (str == "false" || str == "False") {
    return new JsonElement(JsonElement::Type::BOOLEAN, false);
  } else {
    std::cout << "bad input" << std::endl;
    return nullptr;
  }
}

void parseNull() {
  while (source[i] != ',') {
    i++;
  }
  i++;
}

JsonElement *parseNumber() {
  skipSpace();
  std::string num = "";
  int f = 1;
  if (source[i] == '-') {
    f = -1;
    i++;
  }
  while (source[i] == '.' || (source[i] >= '0' && source[i] <= '9')) {
    num += source[i];
    i++;
  }
  i++;
  return new JsonElement(JsonElement::Type::NUMBER, std::stod(num) * f);
}

JsonElement *parseObject() {
  skipSpace();
  if (!checkError('{')) {
    return nullptr;
  } else {
    i++;
  }

  JsonElement *json_element =
      new JsonElement(JsonElement::Type::OBJECT, JsonElement::JsonObject());

  while (source[i] != '}') {
    std::cout << source[i] << std::endl;
    auto key = std::get<std::string>(parseString()->value_);
    // std::cout << "key is:" << key;
    auto value = parseValue();
    // std::cout << std::get<std::string>(value->value_) << std::endl;
    // std::cout << std::get<bool>(value->value_) << std::endl;
    std::get<JsonElement::JsonObject>(json_element->value_)[key] = value;
    skipSpace();
  }
  i++;

  return json_element;
}

JsonElement *parseValue() {
  skipSpace();
  switch (source[i]) {
  case '{':
    return parseObject();
  case '[':
    // return parseArray();
    break;
  case '"':
    return parseString();
  // use multiple case values without using a break between them.
  case 't':
  case 'T':
  case 'f':
  case 'F':
    return parseBoolean();
  case 'n':
    return nullptr;
    // return parseNull();
  default:
    return parseNumber();
  }
  return nullptr;
}
signed main() {
  JsonElement *json_element = parseValue();
  auto json_element_str =
      std::get<JsonElement::JsonObject>(json_element->value_);
  std::cout << std::get<std::string>(json_element_str["hello"]->value_)
            << std::endl;
  auto json_element_num = json_element_str["foo"];
  std::cout << std::get<double>(json_element_num->value_) << std::endl;
  auto json_element_true = json_element_str["urgent"];
  std::cout << std::get<bool>(json_element_true->value_) << std::endl;
  auto json_element_false = json_element_str["expensive"];
  std::cout << std::get<bool>(json_element_false->value_) << std::endl;

  return 0;
}