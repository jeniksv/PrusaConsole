#include <gtest/gtest.h>
#include "printer.hpp"
#include "command.hpp"
#include "history.hpp"
#include "key_actions.hpp"

/*
class KeyActionTest: public testing::Test{
protected:
        std::unique_ptr<key_action_base> key_action_ptr;
        //std::vector<std::string> commands {"a", "b", "c", "d", "e", "f", "g", "h"};

        void SetUp() override{
                if(std::filesystem::exists(".tests_history")){
                        std::filesystem::remove(".tests_history");
                }

                history_ptr = std::make_unique<history>(history(".tests_history"));
        }

        void TearDown() override{
                // tohle byla ta race condition, destruktor se zavolat az potom, co dobehla metoda
                history_ptr.reset();

                if(std::filesystem::exists(".tests_history")){
                        std::filesystem::remove(".tests_history");
                }
        }
};
*/

TEST(KeyActionTest, BackspaceActionTest){
	backspace_action a;
	std::string text = "ahoj";

	a.execute(text);
	ASSERT_EQ(text, "aho");

	a.execute(text);
	ASSERT_EQ(text, "ah");

	a.execute(text);
	ASSERT_EQ(text, "a");

	a.execute(text);
	ASSERT_EQ(text, "");

	a.execute(text);
	ASSERT_EQ(text, "");

	a.execute(text);
	ASSERT_EQ(text, "");
}

TEST(KeyActionTest, SpaceActionTest){
	space_action a;
	std::string text = "ahoj";
	
	a.execute(text);
	ASSERT_EQ(text, "ahoj ");

	a.execute(text);
	ASSERT_EQ(text, "ahoj  ");

	a.execute(text);
	ASSERT_EQ(text, "ahoj   ");

	for(int i = 4; i < text.length(); ++i){
		Term::cout << "\b \b" << std::flush;
	}
}

TEST(KeyActionTest, DefaultTest){
	std::string text = "";

	{
	default_action a("a");
	a.execute(text);
	ASSERT_EQ(text, "a");
	}
	{
	default_action a("h");
	a.execute(text);
	ASSERT_EQ(text, "ah");
	}
	{
	default_action a("o");
	a.execute(text);
	ASSERT_EQ(text, "aho");
	}
	{
	default_action a("j");
	a.execute(text);
	ASSERT_EQ(text, "ahoj");
	}

	// console clean up
	for(int i = 0; i < text.length(); ++i){
		Term::cout << "\b \b" << std::flush;
	}
}

TEST(KeyActionTest, EnterActionTest){
	{
	history h(".tests_history");
	printer p("mock");
	enter_action a(h, p);
	std::string text = "ahoj";
	
	a.execute(text);
	
	// assert line was added to history
	ASSERT_EQ(h.get_previous(), "ahoj");
	}
	
	if(std::filesystem::exists(".tests_history")){
		std::filesystem::remove(".tests_history");
	}
}
