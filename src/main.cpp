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
}
)";

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
    std::cout << "error" << std::endl;
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

void parseBoolean() {
  while (source[i] != ',') {
    i++;
  }
  i++;
}

void parseNull() {
  while (source[i] != ',') {
    i++;
  }
  i++;
}

void parseNumber() {
  while (source[i] != ',') {
    i++;
  }
  i++;
}

JsonElement *parseObject() {
  skipSpace();
  if (!checkError('{')) {
    return nullptr;
  } else {
    i++;
  }

  JsonElement *json_element = new JsonElement(JsonElement::Type::BEGIN_OBJECT,
                                              JsonElement::JsonObject());
  while (source[i] != '}') {
    auto key = std::get<std::string>(parseString()->value_);
    auto value = parseValue();
    std::get<JsonElement::JsonObject>(json_element->value_)[key] = value;
    skipSpace();
  }
  i++;
  return json_element;
}

JsonElement *parseValue() {
  skipSpace();
  //   std::cout << "source" << source[i] << std::endl;
  switch (source[i]) {
  case '{':
    return parseObject();
  case '[':
    // return parseArray();
    break;
  case '"':
    return parseString();
    break;
  // use multiple case values without using a break between them.
  case 't':
  case 'f':
    // return parseBoolean();
    break;
  case 'n':
    // return parseNull();
  default:
    break;
    // return parseNumber();
  }
}
signed main() {
  //   std::cout << source << std::endl;
  JsonElement *json_element = parseValue();
  //   std::cout <<
  //   std::get<JsonElement::JsonObject>(json_element->value_)["hello"]
  //             << std::endl;
  return 0;
}