#include <set>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <filesystem>
#include <gtest/gtest.h>
#include "tab_completion.hpp"

class TabCompletionTest: public testing::Test{
protected:
	std::unique_ptr<tab_completion> tab_ptr;

	void SetUp() override{
		SetUpMockFileSystem();

		// TODO switch for real commands
		tab_ptr = std::make_unique<tab_completion>(tab_completion({
			"a", "abcdx", "abcdy", "abcdz",
			"IMG20230302235930.jpg", "IMG20230303013145.jpg", "IMG20230303013148.jpg", "IMG20230303015757.jpg", "IMG20230303015801.jpg",
			"Desktop", "Documents", "Downloads", "MFF", "Pictures", "PrusaConsole", "Work"		
		}));
	}

        void TearDown() override{
		// asi je hezky po sobe uklidit
                // std::filesystem::remove_all("filesystem_mock");
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
		// TODO create rest of filesystem
	}

	void CreateFile(const std::string& name){
		std::ofstream f(name);
		if(f.is_open()){
			f.close();
		}
	}
};


TEST_F(TabCompletionTest, GetCommandMatch){
	EXPECT_EQ(tab_ptr->get_command_match("a"), "a");
	EXPECT_EQ(tab_ptr->get_command_match("abc"), "abcd");
	EXPECT_EQ(tab_ptr->get_command_match("IM"), "IMG2023030");
	EXPECT_EQ(tab_ptr->get_command_match("D"), "D");
	EXPECT_EQ(tab_ptr->get_command_match("X"), "");
}

TEST_F(TabCompletionTest, GetPathMatch){
	std::string current = "filesystem_m";
	
	current = tab_ptr->get_path_match(current);
	EXPECT_EQ(current, "filesystem_mock");
	
	current.append("/Pi");
	current = tab_ptr->get_path_match(current);
	EXPECT_EQ(current, "filesystem_mock/Pictures");

	current.append("/I");
	current = tab_ptr->get_path_match(current);
	EXPECT_EQ(current, "filesystem_mock/Pictures/IMG2023030");

	current.append("3");
	current = tab_ptr->get_path_match(current);
	EXPECT_EQ(current, "filesystem_mock/Pictures/IMG2023030301");

	current.append("5");
	current = tab_ptr->get_path_match(current);
	EXPECT_EQ(current, "filesystem_mock/Pictures/IMG20230303015");

	current.append("7");
	current = tab_ptr->get_path_match(current);
	EXPECT_EQ(current, "filesystem_mock/Pictures/IMG20230303015757");
}

TEST_F(TabCompletionTest, GetCommandMatches){
	std::vector<std::string> expected_matches_abc = {"abcdx", "abcdy", "abcdz"};
	EXPECT_EQ(tab_ptr->get_command_matches("abc"), expected_matches_abc);

	std::vector<std::string> expected_matches_img = {"IMG20230302235930.jpg", "IMG20230303013145.jpg", "IMG20230303013148.jpg", "IMG20230303015757.jpg", "IMG20230303015801.jpg"};
	EXPECT_EQ(tab_ptr->get_command_matches("IMG"), expected_matches_img);
	// TODO add more test cases
}

