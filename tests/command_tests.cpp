#include "command.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>

class mock_command : public concrete_command_base {
public:
    using concrete_command_base::concrete_command_base;
    MOCK_METHOD(command_result, execute, (std::stringstream&), (override));
    MOCK_METHOD(std::string, help, (), (override));
};
/*
// Test fixture for command class
class CommandTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialization code specific to each test case
    }

    void TearDown() override {
        // Cleanup code specific to each test case
    }
};
*/
// Test fixture for concrete_command_base class
class ConcreteCommandBaseTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        // Initialization code specific to each test case
    }

    void TearDown() override
    {
        // Cleanup code specific to each test case
    }
};

// Test fixture for composite_command class
class CompositeCommandTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        // Initialization code specific to each test case
    }

    void TearDown() override
    {
        // Cleanup code specific to each test case
    }
};

// Test case for command class
/*
TEST_F(CommandTest, GetName) {
    // Test the get_name() function of the command class
    // Instantiate the command class with a name and leaf value
    command cmd("test_command", true);

    // Check if the get_name() function returns the correct name
    EXPECT_EQ(cmd.get_name(), "test_command");
}*/

// Test case for concrete_command_base class
TEST_F(ConcreteCommandBaseTest, Execute)
{
    // Test the execute() function of the concrete_command_base class
    // Instantiate the mock class for command_result
    // mock_command mock("mock command");

    // Instantiate the mock class for concrete_command_base
    // MockConcreteCommandBase concreteCmd("test_command");
    // std::stringstream ss("tilt home");
    // mock.execute(ss);
    // Set up expectations for the mock objects

    // EXPECT_CALL(mock, execute(ss)); //.WillOnce(testing::Return(mockResult));

    // Call the execute() function and check if it returns the expected result
    // EXPECT_EQ(concreteCmd.execute(std::stringstream()), mockResult);
}

// Test case for composite_command class
TEST_F(CompositeCommandTest, AddCommand)
{
    // Test the add_command() function of the composite_command class
    // Instantiate the composite_command class
    composite_command c("root");

    c.add_command(std::make_shared<composite_command>("child_1"));
    c.add_command(std::make_shared<composite_command>("child_2"));
    c.add_command(std::make_shared<composite_command>("child_3"));

    // Check if the get_children() function returns the correct number of children
    EXPECT_EQ(c.get_children().size(), 3);

    for (const auto& child : c.get_children()) {
        EXPECT_FALSE(child->is_leaf());
    }
}
