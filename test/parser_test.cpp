#include "../src/parser.h"
#include <gtest/gtest.h>
#include <memory>
#include <string>

// Define a test fixture class for setting up parser objects
class JsonParserTest : public ::testing::Test {
protected:
  std::unique_ptr<Parser> parser;

  void SetUp() override {
    // Setup code can be added here if needed for all tests
  }

  void TearDown() override {
    // Cleanup code can be added here if needed for all tests
  }
};

// Test parsing a simple string value
TEST_F(JsonParserTest, ParsesString) {
  std::string json = R"({"name": "John Doe"})";
  parser = std::make_unique<Parser>(json);
  JsonElement *result = parser->parse();
  auto result_str = std::get<std::string>(
      std::get<JsonElement::JsonObject>(result->value_)["name"]->value_);
  ASSERT_EQ(result_str, "John Doe");
}

// Test parsing a number
TEST_F(JsonParserTest, ParsesNumber) {
  std::string json = R"({"age": 30})";
  parser = std::make_unique<Parser>(json);
  JsonElement *result = parser->parse();
  auto result_num = std::get<double>(
      std::get<JsonElement::JsonObject>(result->value_)["age"]->value_);
  ASSERT_DOUBLE_EQ(result_num, 30.0);
}

// Test parsing a boolean true value
TEST_F(JsonParserTest, ParsesBooleanTrue) {
  std::string json = R"({"valid": true})";
  parser = std::make_unique<Parser>(json);
  JsonElement *result = parser->parse();
  auto result_bool = std::get<bool>(
      std::get<JsonElement::JsonObject>(result->value_)["valid"]->value_);
  ASSERT_TRUE(result_bool);
}

// Test parsing a boolean false value
TEST_F(JsonParserTest, ParsesBooleanFalse) {
  std::string json = R"({"valid": false})";
  parser = std::make_unique<Parser>(json);
  JsonElement *result = parser->parse();
  auto result_bool = std::get<bool>(
      std::get<JsonElement::JsonObject>(result->value_)["valid"]->value_);
  ASSERT_FALSE(result_bool);
}

// Test parsing a null value
TEST_F(JsonParserTest, ParsesNull) {
  std::string json = R"({"item": null})";
  parser = std::make_unique<Parser>(json);
  JsonElement *result = parser->parse();
  auto result_null = std::get<JsonElement::JsonObject>(result->value_)["item"];
  ASSERT_EQ(result_null->type(), JsonElement::Type::NULL_VALUE);
}

// Test parsing an array
TEST_F(JsonParserTest, ParsesArray) {
  std::string json = R"({"data": [1, 2, 3]})";
  parser = std::make_unique<Parser>(json);
  JsonElement *result = parser->parse();
  auto result_array = std::get<JsonElement::JsonArray>(
      std::get<JsonElement::JsonObject>(result->value_)["data"]->value_);
  ASSERT_EQ(result_array.size(), 3); // Check if array size is correct
  ASSERT_EQ(std::get<double>(result_array[0]->value_),
            1.0); // Check first element
  ASSERT_EQ(std::get<double>(result_array[1]->value_),
            2.0); // Check second element
  ASSERT_EQ(std::get<double>(result_array[2]->value_),
            3.0); // Check third element
}

// Test parsing an object
TEST_F(JsonParserTest, ParsesObject) {
  std::string json = R"({"person": {"name": "John", "age": 30}})";
  parser = std::make_unique<Parser>(json);
  JsonElement *result = parser->parse();
  auto result_object = std::get<JsonElement::JsonObject>(
      std::get<JsonElement::JsonObject>(result->value_)["person"]->value_);
  ASSERT_EQ(std::get<std::string>(result_object["name"]->value_),
            "John"); // Check name field
  ASSERT_EQ(std::get<double>(result_object["age"]->value_),
            30.0); // Check age field
}

// Main function to run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
