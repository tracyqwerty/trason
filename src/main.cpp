#include "parser.h"

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

// use static to make source internal linkage
static auto source = R"(
{
    "hello": "world",
    "foo": 1.01,
    "urgent":    True,
    "expensive":    False,
    "bazzzz": null,
    "animals": [
        "dog",
        "cat",
        "penguin"
    ],
}
)";

signed main() {
  Parser parse(source);
  JsonElement *json_element = parse.parse();
  auto json_element_obj =
      std::get<JsonElement::JsonObject>(json_element->value_);

  // test string
  std::cout << std::get<std::string>(json_element_obj["hello"]->value_)
            << std::endl;
  // test number
  auto json_element_num = json_element_obj["foo"];
  std::cout << std::get<double>(json_element_num->value_) << std::endl;
  // test boolean
  auto json_element_true = json_element_obj["urgent"];
  std::cout << std::get<bool>(json_element_true->value_) << std::endl;
  auto json_element_false = json_element_obj["expensive"];
  std::cout << std::get<bool>(json_element_false->value_) << std::endl;
  // test null
  auto json_element_null = json_element_obj["bazzzz"];
  std::cout << std::get<bool>(json_element_null->value_) << std::endl;
  // test array
  auto json_element_array =
      std::get<JsonElement::JsonArray>(json_element_obj["animals"]->value_);
  for (auto &i : json_element_array) {
    std::cout << std::get<std::string>(i->value_) << std::endl;
  }

  return 0;
}