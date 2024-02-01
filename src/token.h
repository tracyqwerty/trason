#include <string>
class Token {
public:
  enum Type {
    BRACE_OPEN, // '{'
    BRACE_CLOSE,
    BRACKET_OPEN, // '['
    BRACKET_CLOSE,
    COMMA, // ','
    COLON, // ':'
    STRING,
    NUMBER,
    BOOLEAN,
    NULL_VALUE,
    END_OF_FILE
  };

  Type type_;

  // many thanks to c++17!!!
  // https://stackoverflow.com/questions/51622016/how-to-delete-a-string-object-which-is-a-member-variable-of-a-c-union
  std::variant<std::string, double, bool> value_;

  Token(Type type, const std::variant<std::string, double, bool> &value)
      : type_(type), value_(value) {}
};