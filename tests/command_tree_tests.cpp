#include <sstream>
#include <gtest/gtest.h>
// TODO #include <gmock/gmock.h>
#include "command.hpp"
#include "command_tree.hpp"
#include "command_tree_builder.hpp"

class concrete_command_mock : public concrete_command_base{
public:
	concrete_command_mock(const std::string& name) : concrete_command_base(name) {}

        command_result execute(std::stringstream&) override { return command_result::NOT_IMPLEMENTED; }

        std::string help() override { return std::string(); }

	
	//MOCK_METHOD(command_result, execute, (std::stringstream&), (override));
	// MOCK_METHOD(std::string, help, (), (override));
};

class CommandTreeTest : public testing::Test{
protected:
	command_tree _tree;
	
	void SetUp() override {
		// TODO mock tree class for tests
		_tree = command_tree_builder()
			.add_composite_command("tower")
				.add_composite_command("position")
					.add_concrete_command(std::make_shared<concrete_command_mock>("get"))
					.add_concrete_command(std::make_shared<concrete_command_mock>("set"))
				.end_composite_command()
			.end_composite_command()
			.add_core_commands()
			.build();
	}
};

TEST_F(CommandTreeTest, GetCompleteOptions){
	std::vector<std::string> options = _tree.get_complete_options("h");
	
	std::vector<std::string> expected_options = {"help"};

	EXPECT_EQ(options, expected_options);
}

TEST_F(CommandTreeTest, CompleteCommand){
	std::string command = "he";
	_tree.complete_command(command);

	std::string expected_command = "help";

	EXPECT_EQ(command, expected_command);
}

TEST_F(CommandTreeTest, CommandExecution){
	std::string command = "tower position set 1000";
	command_result result = _tree.execute_command(command);

	// EXPECT_CALL();

}
