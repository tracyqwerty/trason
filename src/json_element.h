#ifndef JSON_ELEMENT_H
#define JSON_ELEMENT_H

#include <map>
#include <string>
#include <variant>
#include <vector>
class JsonElement {
public:
  using JsonArray = std::vector<JsonElement *>;
  using JsonObject = std::map<std::string, JsonElement *>;

  enum Type { ARRAY, OBJECT, STRING, NUMBER, BOOLEAN, NULL_VALUE };

  JsonElement(JsonElement::Type type,
              const std::variant<JsonArray, JsonObject, std::string, double,
                                 bool> &value)
      : type_(type), value_(value) {}

  Type type() const { return type_; }

  // many thanks to c++17!!!
  // https://stackoverflow.com/questions/51622016/how-to-delete-a-string-object-which-is-a-member-variable-of-a-c-union
  std::variant<JsonArray, JsonObject, std::string, double, bool> value_;

private:
  // type_ is pre-set, while value_ may be modified
  Type type_;
};

#endif // JSON_ELEMENT_H