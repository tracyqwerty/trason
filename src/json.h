#include <string>
class JsonValue {
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

  //   union TokenValue {
  //     std::string
  //         string_value_; // std::string type is a non-trivially copyable
  //                        // type. Non-trivial types within a union prevent
  //                        the
  //                        // compiler from automatically generating a default
  //                        copy
  //                        // constructor and copy assignment operator for the
  //                        union
  //                        // or any class containing it. This is because the
  //                        // compiler cannot determine which member of the
  //                        union is
  //                        // active and thus doesn't know how to correctly
  //                        copy the
  //                        // union's content without user guidance.
  //                        ---------------
  //                        // When you include a non-trivially destructible
  //                        type
  //                        // like std::string in a union, you must manually
  //                        manage
  //                        // the construction and destruction of that type
  //                        because
  //                        // the union itself does not automatically call
  //                        // constructors or destructors for its members. This
  //                        // means you need to use placement new to construct
  //                        the
  //                        // string and explicitly call the destructor for the
  //                        // string when the union is being destroyed or
  //                        // overwritten.
  //     double number_value_;
  //     bool bool_value_;

  //     // why do we need this?
  //     TokenValue() {}
  //     TokenValue(const std::string &string_value) {
  //       // operagor new, placement new???
  //       new (&string_value_) std::string(string_value);
  //     }
  //     // trival types, no need of const reference
  //     TokenValue(double number_value) : number_value_(number_value) {}
  //     TokenValue(bool bool_value) : bool_value_(bool_value) {}
  //     ~TokenValue() {
  //       // TODO: std::string is a non-trivially destructible type, so we need
  //       to
  //       // explicitly call the destructor -- Really? Yes!
  //       //   if (string_value_.size() > 0) {
  //       //     string_value_.~basic_string();
  //       //   }
  //       if (type_ == Type::STRING) {
  //         value_.string_value_.std::string::~string();
  //       }
  //     }
  // };
  // TokenValue value_;

  JsonValue(Type type, const std::variant<std::string, double, bool> &value)
      : type_(type), value_(value) {
    // switch (type_) {
    // case Type::STRING:
    //   // operagor new, placement new???
    //   new (&value_.string_value_) std::string(value.string_value_);
    //   //   value_.string_value_ = value.string_value_;
    //   break;
    // case Type::NUMBER:
    //   value_.number_value_ = value.number_value_;
    //   break;
    // case Type::BOOLEAN:
    //   value_.bool_value_ = value.bool_value_;
    //   break;
    // default:
    //   break;
    // }
  }
};