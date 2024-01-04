#include <string>
#include <gtest/gtest.h>
#include "parser.hpp"

class CommandParserTest: public testing::Test{
protected:
        std::unique_ptr<command_parser> parser_ptr;
	std::vector<std::string> args {"a", "b", "c" };

        void SetUp() override{
                parser_ptr = std::make_unique<command_parser>();
        }

        void TearDown() override{
                parser_ptr.reset();
        }
};

TEST_F(CommandParserTest, Initialization) {
	ASSERT_FALSE(parser_ptr->get_name().has_value());
	ASSERT_FALSE(parser_ptr->get_arguments().has_value());
}

TEST_F(CommandParserTest, ProcessEmptyString) {
	parser_ptr->process("");

	ASSERT_FALSE(parser_ptr->get_name().has_value());
	ASSERT_FALSE(parser_ptr->get_arguments().has_value());
}

TEST_F(CommandParserTest, ProcessValidCommand) {
	parser_ptr->process("command a b c");

	ASSERT_TRUE(parser_ptr->get_name().has_value());
	ASSERT_EQ(parser_ptr->get_name().value(), "command");

	ASSERT_TRUE(parser_ptr->get_arguments().has_value());
	ASSERT_EQ(parser_ptr->get_arguments().value(), args);
}

TEST_F(CommandParserTest, ProcessNoArgumentsCommand) {
	parser_ptr->process("command");
	
	ASSERT_TRUE(parser_ptr->get_name().has_value());
	ASSERT_EQ(parser_ptr->get_name().value(), "command");

	ASSERT_FALSE(parser_ptr->get_arguments().has_value());
}

TEST_F(CommandParserTest, ProcessMultipleSpacesBetweenArgs) {
	parser_ptr->process("command   a   b   c");

	ASSERT_TRUE(parser_ptr->get_name().has_value());
	ASSERT_EQ(parser_ptr->get_name().value(), "command");

	ASSERT_TRUE(parser_ptr->get_arguments().has_value());
	ASSERT_EQ(parser_ptr->get_arguments().value(), args);
}

TEST_F(CommandParserTest, ProcessExtraSpacesAtBeginningAndEnd) {
	parser_ptr->process("   command a   b  c   ");

	ASSERT_TRUE(parser_ptr->get_name().has_value());
	ASSERT_EQ(parser_ptr->get_name().value(), "command");

	ASSERT_TRUE(parser_ptr->get_arguments().has_value());
	ASSERT_EQ(parser_ptr->get_arguments().value(), args);
}
