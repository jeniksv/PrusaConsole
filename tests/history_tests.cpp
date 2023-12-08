#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <gtest/gtest.h>
#include "history.hpp"

class HistoryTest: public testing::Test{
protected:
	std::unique_ptr<history> history_ptr;
	std::vector<std::string> commands {"a", "b", "c", "d", "e", "f", "g", "h"};

	void SetUp() override{
		history_ptr = std::make_unique<history>(history(".tests_history"));
	}

	void TearDown(){
		if(std::filesystem::exists(".tests_history")){
			std::filesystem::remove(".tests_history");
		}	
	}
};

TEST_F(HistoryTest, AddAndGetCommands) {
	history_ptr->add("a");
	ASSERT_EQ(history_ptr->get_current(), "a");
	
	history_ptr->add("b");
	ASSERT_EQ(history_ptr->get_current(), "b");
	
	history_ptr->add("c");
	ASSERT_EQ(history_ptr->get_current(), "c");
}

TEST_F(HistoryTest, MoveNextAndBackAnd) {
	for(const std::string& s : commands){
		history_ptr->add(s);
	}

	for(int i=7; i >= 0; --i){
		ASSERT_EQ(history_ptr->get_current(), commands[i]);
		history_ptr->move_back();
	}
}

TEST_F(HistoryTest, WriteFetchHistory) {
	for(const std::string& s : commands){
		history_ptr->add(s);
	}

	// Write
	history_ptr.reset();
	
	// Fetch
	history_ptr = std::make_unique<history>(history(".tests_history"));

	for(int i=7; i >= 0; --i){
		ASSERT_EQ(history_ptr->get_current(), commands[i]);
		history_ptr->move_back();
	}
}

/*
// NOT IMPLEMENTED
TEST(HistoryTest, PatternMatchingEnabled) {
	history hist("test_history.txt");

	hist.add("apple");
	hist.add("banana");
	hist.add("orange");

	hist.enable_pattern_matching("app");

	ASSERT_EQ(hist.get_current(), "apple");

	hist.move_next();
	ASSERT_EQ(hist.get_current(), "");
}

TEST(HistoryTest, PatternMatchingDisabled) {
	history hist("test_history.txt");

	hist.add("apple");
	hist.add("banana");
	hist.add("orange");

	hist.enable_pattern_matching("app");
	hist.disable_pattern_matching();

	ASSERT_EQ(hist.get_current(), "orange");
}
*/
