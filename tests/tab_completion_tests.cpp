#include <set>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "tab_completion.hpp"


const std::set<std::string> commands = {
	"a", "abcdx", "abcdy", "abcdz",
	"IMG20230302235930.jpg", "IMG20230303013145.jpg", "IMG20230303013148.jpg", "IMG20230303015757.jpg", "IMG20230303015801.jpg",
	"Desktop", "Documents", "Downloads", "MFF", "Pictures", "PrusaConsole", "Work"
};

TEST(TabCompletionTest, GetCommandMatch){
	tab_completion tab(commands);

	EXPECT_EQ(tab.get_command_match("a"), "a");
	EXPECT_EQ(tab.get_command_match("abc"), "abcd");
	EXPECT_EQ(tab.get_command_match("IM"), "IMG2023030");
	EXPECT_EQ(tab.get_command_match("D"), "D");
	EXPECT_EQ(tab.get_command_match("X"), "");
}

TEST(TabCompletionTest, GetPathMatch){
	// TODO create fake filesystem for testing
	tab_completion tab(commands);

	// EXPECT_EQ(tab.get_path_match("Doc"), "Documents");
}

TEST(TabCompletionTest, GetCommandMatches){
	tab_completion tab(commands);

	std::vector<std::string> expected_matches_abc = {"abcdx", "abcdy", "abcdz"};
	EXPECT_EQ(tab.get_command_matches("abc"), expected_matches_abc);

	std::vector<std::string> expected_matches_img = {"IMG20230302235930.jpg", "IMG20230303013145.jpg", "IMG20230303013148.jpg", "IMG20230303015757.jpg", "IMG20230303015801.jpg"};
	EXPECT_EQ(tab.get_command_matches("IMG"), expected_matches_img);
	// TODO add more test cases
}

