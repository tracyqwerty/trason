#include "../src/token.h"
#include <gtest/gtest.h>

TEST(Token, test_string) {
  std::variant<std::string, double, bool> token_value("hello");
  Token json_value(Token::Type::STRING, token_value);
  EXPECT_EQ(json_value.type_, Token::Type::STRING);
  EXPECT_EQ(std::get<std::string>(json_value.value_), "hello");
}

TEST(Token, test_number) {
  std::variant<std::string, double, bool> token_value(1.0);
  Token json_value(Token::Type::NUMBER, token_value);
  EXPECT_EQ(json_value.type_, Token::Type::NUMBER);
  EXPECT_EQ(std::get<double>(json_value.value_), 1.0);
}

TEST(Token, test_boolean) {
  std::variant<std::string, double, bool> token_value(true);
  Token json_value(Token::Type::BOOLEAN, token_value);
  EXPECT_EQ(json_value.type_, Token::Type::BOOLEAN);
  EXPECT_EQ(std::get<bool>(json_value.value_), true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}