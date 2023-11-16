#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "history.hpp"

TEST(HistoryTest, AddAndGetCommands) {
	history h;

	h.add("a");
	ASSERT_EQ(h.get_current(), "");
	
	h.add("b");
	ASSERT_EQ(h.get_current(), "");
	
	h.add("c");
	ASSERT_EQ(h.get_current(), "");
}

TEST(HistoryTest, MoveNextAndBackAnd) {
	history h;
	std::vector<std::string> commands {"a", "b", "c", "d", "e", "f", "g", "h"};

	for(const std::string& s : commands){
		h.add(s);
	}

	for(int i=7; i >= 0; --i){
		h.move_back();
		ASSERT_EQ(h.get_current(), commands[i]);
	}
}
/*
TEST(HistoryTest, FetchHistory) {

}

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
