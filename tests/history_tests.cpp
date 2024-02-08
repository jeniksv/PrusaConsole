#include "history.hpp"
#include <filesystem>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class HistoryTest : public testing::Test {
protected:
    std::unique_ptr<history> history_ptr;
    std::vector<std::string> commands { "a", "b", "c", "d", "e", "f", "g", "h" };

    void SetUp() override
    {
        if (std::filesystem::exists(".tests_history")) {
            std::filesystem::remove(".tests_history");
        }

        history_ptr = std::make_unique<history>(history(".tests_history"));
    }

    void TearDown() override
    {
        // tohle byla ta race condition, destruktor se zavolat az potom, co dobehla metoda
        history_ptr.reset();

        if (std::filesystem::exists(".tests_history")) {
            std::filesystem::remove(".tests_history");
        }
    }
};

TEST_F(HistoryTest, AddAndGetCommands)
{
    history_ptr->add("a");
    ASSERT_EQ(history_ptr->get_current(), "");

    history_ptr->add("b");
    ASSERT_EQ(history_ptr->get_current(), "");
}

TEST_F(HistoryTest, MoveNextAndBack)
{
    for (const std::string& s : commands) {
        history_ptr->add(s);
    }

    for (int i = static_cast<int>(commands.size()) - 1; i >= 0; --i) {
        history_ptr->move_back();
        ASSERT_EQ(history_ptr->get_current(), commands[i]);
    }
}

TEST_F(HistoryTest, WriteFetchHistory)
{
    for (const std::string& s : commands) {
        history_ptr->add(s);
    }

    // Write
    history_ptr.reset();

    // Fetch
    history_ptr = std::make_unique<history>(history(".tests_history"));

    for (int i = static_cast<int>(commands.size()) - 1; i >= 0; --i) {
        history_ptr->move_back();
        ASSERT_EQ(history_ptr->get_current(), commands[i]);
    }
}

TEST_F(HistoryTest, GetNextAndPrevious)
{
    for (const std::string& s : commands) {
        history_ptr->add(s);
    }

    ASSERT_GE(commands.size(), 4);

    ASSERT_EQ(history_ptr->get_previous(), commands[static_cast<int>(commands.size()) - 1]);
    ASSERT_EQ(history_ptr->get_previous(), commands[static_cast<int>(commands.size()) - 2]);
    ASSERT_EQ(history_ptr->get_previous(), commands[static_cast<int>(commands.size()) - 3]);
    ASSERT_EQ(history_ptr->get_next(), commands[static_cast<int>(commands.size()) - 2]);

    history_ptr->reset();

    for (int i = static_cast<int>(commands.size()) - 1; i > -10; --i) {
        std::string expected = i < 0 ? commands[0] : commands[i];
        ASSERT_EQ(history_ptr->get_previous(), expected);
    }

    for (size_t i = 0; i < static_cast<int>(commands.size()) + 10; ++i) {
        std::string expected = i < static_cast<int>(commands.size()) - 1 ? commands[i + 1] : "";
        ASSERT_EQ(history_ptr->get_next(), expected);
    }
}
