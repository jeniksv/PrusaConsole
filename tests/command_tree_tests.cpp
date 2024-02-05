#include <map>
#include <fstream>
#include <filesystem>
#include <gtest/gtest.h>
// TODO #include <gmock/gmock.h>
#include "printer.hpp"
#include "command.hpp"
#include "command_tree.hpp"
#include "command_tree_builder.hpp"

/* TODO
class concrete_command_mock : public concrete_command_base{
public:
	concrete_command_mock(const std::string& name) : concrete_command_base(name) {}

	command_result execute(std::stringstream&) override { return command_result::NOT_IMPLEMENTED; }

	std::string help() override { return std::string(); }

	
	//MOCK_METHOD(command_result, execute, (std::stringstream&), (override));
	// MOCK_METHOD(std::string, help, (), (override));
};
*/

class CommandTreeTest : public testing::Test{
protected:
	printer p;
	command_tree t;

	void SetUp() override {
		p = printer("mock");
		t = p.get_command_tree();

		SetUpMockFileSystem();
	}

	void SetUpMockFileSystem(){
		if(std::filesystem::exists("filesystem_mock")){
			return;
		}

		std::filesystem::create_directory("filesystem_mock");
		std::filesystem::create_directory("filesystem_mock/Pictures");
		CreateFile("filesystem_mock/Pictures/IMG20230302235930");
		CreateFile("filesystem_mock/Pictures/IMG20230303013145");
		CreateFile("filesystem_mock/Pictures/IMG20230303013148");
		CreateFile("filesystem_mock/Pictures/IMG20230303015757");
		CreateFile("filesystem_mock/Pictures/IMG20230303015801");
		std::filesystem::create_directory("filesystem_mock/Downloads");
		std::filesystem::create_directory("filesystem_mock/Documents");
		// TODO create rest of filesystem
	}

	void CreateFile(const std::string& name){
		std::ofstream f(name);
		if(f.is_open()){
			f.close();
		}
	}
};

TEST_F(CommandTreeTest, UnknowCommand){
	EXPECT_EQ(t.execute_command("a"), command_result::UNKNOWN_COMMAND);
	EXPECT_EQ(t.execute_command("b"), command_result::UNKNOWN_COMMAND);
	EXPECT_EQ(t.execute_command("tower pos"), command_result::UNKNOWN_COMMAND);
	EXPECT_EQ(t.execute_command("tilt position"), command_result::UNKNOWN_COMMAND);
}

TEST_F(CommandTreeTest, GetCompleteOptions){
	// map<current_command, expected_options>
	std::map<std::string, std::vector<std::string>> test_data = {
		{"h", {"help"}},
		{"e", {"exit"}},
		{"t", {"tilt", "tower"}},
		{"print s", {"start", "stop"}},
		{"tower position ", {"get", "set"}}
	};

	for(const auto& pair : test_data){
		std::vector<std::string> options = t.get_complete_options(pair.first);
		EXPECT_EQ(options, pair.second);
	}
}

TEST_F(CommandTreeTest, GetPathOptions){
	// map<current_command, completed_current_command_with_patht>
	std::map<std::string, std::vector<std::string>> test_data = {
		{"print start InvalidDirectory", {}},
		{"print start fi", {"filesystem_mock"}},
		{"print start filesystem_mock/P", {"Pictures"}},
		{
			"print start filesystem_mock/Pictures/IMG",
			{"IMG20230303013148", "IMG20230303015801", "IMG20230303013145", "IMG20230302235930", "IMG20230303015757"}
		},
		{"print start filesystem_mock/Pictures/IMG20230303013", {"IMG20230303013148", "IMG20230303013145"}},
		{"print start filesystem_mock/D", {"Documents", "Downloads"}},
	};

	for(const auto& pair : test_data){
		std::vector<std::string> options = t.get_complete_options(pair.first);
		EXPECT_EQ(options, pair.second);
	}
}

TEST_F(CommandTreeTest, CompleteCommand){
	// map<current_command, completed_current_command>
	std::map<std::string, std::string> test_data = {
		{"h", "help"},
		{"t", "t"},
		{"to", "tower"},
		{"tower p", "tower position"},
		{"tower position s", "tower position set"},
		{"pr", "print"},
		{"print s", "print st"},
		{"print sta", "print start"},
		{"abc", "abc"},
		{"ahoj", "ahoj"},
	};

	for(const auto& pair : test_data){
		std::string current = pair.first;
		t.complete_command(current);
		EXPECT_EQ(current, pair.second);
	}
}

TEST_F(CommandTreeTest, CompletePath){
	// map<current_command, completed_current_command_with_patht>
	std::map<std::string, std::string> test_data = {
		{"print start fi", "print start filesystem_mock/"},
		{"print start filesystem_mock/P", "print start filesystem_mock/Pictures/"},
		{"print start filesystem_mock/Pictures/IMG", "print start filesystem_mock/Pictures/IMG2023030"},
		{"print start filesystem_mock/Pictures/IMG20230303", "print start filesystem_mock/Pictures/IMG2023030301"},
		{"print start filesystem_mock/Pictures/IMG20230303013", "print start filesystem_mock/Pictures/IMG2023030301314"},
		{"print start filesystem_mock/Pictures/IMG20230303013145", "print start filesystem_mock/Pictures/IMG20230303013145"},
		{"print start filesystem_mock/D", "print start filesystem_mock/Do"},
	};

	for(const auto& pair : test_data){
		std::string current = pair.first;
		t.complete_command(current);
		EXPECT_EQ(current, pair.second);
	}
}

TEST_F(CommandTreeTest, CommandExecution){
	/*
	std::string command = "tower position set 1000";
	command_result result = t.execute_command(command);

	EXPECT_CALL();
	// check if mock got called
	*/
}
