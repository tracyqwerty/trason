#include "../src/json.h"
#include <gtest/gtest.h>

TEST(JsonValue, test_string) {
  std::variant<std::string, double, bool> token_value("hello");
  JsonValue json_value(JsonValue::Type::STRING, token_value);
  EXPECT_EQ(json_value.type_, JsonValue::Type::STRING);
  EXPECT_EQ(std::get<std::string>(json_value.value_), "hello");
}

TEST(JsonValue, test_number) {
  std::variant<std::string, double, bool> token_value(1.0);
  JsonValue json_value(JsonValue::Type::NUMBER, token_value);
  EXPECT_EQ(json_value.type_, JsonValue::Type::NUMBER);
  EXPECT_EQ(std::get<double>(json_value.value_), 1.0);
}

TEST(JsonValue, test_boolean) {
  std::variant<std::string, double, bool> token_value(true);
  JsonValue json_value(JsonValue::Type::BOOLEAN, token_value);
  EXPECT_EQ(json_value.type_, JsonValue::Type::BOOLEAN);
  EXPECT_EQ(std::get<bool>(json_value.value_), true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}