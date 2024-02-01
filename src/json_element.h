#include <map>
#include <string>
#include <variant>
class JsonElement {
public:
  using JsonArray = std::vector<JsonElement *>;
  using JsonObject = std::map<std::string, JsonElement *>;

  enum Type {
    BEGIN_ARRAY,
    END_ARRAY,
    BEGIN_OBJECT,
    END_OBJECT,
    STRING,
    NUMBER,
    BOOLEAN,
    NULL_VALUE
  };

  Type type_;
  std::variant<JsonArray, JsonObject, std::string, double, bool> value_;

  JsonElement(JsonElement::Type type,
              const std::variant<JsonArray, JsonObject, std::string, double,
                                 bool> &value)
      : type_(type), value_(value) {}
};