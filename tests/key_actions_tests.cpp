#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "printer.hpp"
#include "command.hpp"
#include "history.hpp"
#include "key_actions.hpp"
#include "cpp-terminal/key.hpp"

class KeyActionTest: public testing::Test{
protected:
	history h {".tests_history"};
	printer p {printer_model::MOCK};
	key_action_factory f {h, p};
        std::unique_ptr<key_action_base> key_action_ptr;

        void TearDown() override{
		key_action_ptr.reset();

                if(std::filesystem::exists(".tests_history")){
                        std::filesystem::remove(".tests_history");
                }
        }
};


TEST_F(KeyActionTest, BackspaceActionTest){
	key_action_ptr = f.get_action(Term::Key::Backspace);	
	std::string text = "ahoj";

	key_action_ptr->execute(text);
	ASSERT_EQ(text, "aho");

	key_action_ptr->execute(text);
	ASSERT_EQ(text, "ah");

	key_action_ptr->execute(text);
	ASSERT_EQ(text, "a");

	key_action_ptr->execute(text);
	ASSERT_EQ(text, "");

	key_action_ptr->execute(text);
	ASSERT_EQ(text, "");

	key_action_ptr->execute(text);
	ASSERT_EQ(text, "");
}

TEST_F(KeyActionTest, SpaceActionTest){
	key_action_ptr = f.get_action(Term::Key::Space);
	
	std::string text = "ahoj";
	
	key_action_ptr->execute(text);
	ASSERT_EQ(text, "ahoj ");

	key_action_ptr->execute(text);
	ASSERT_EQ(text, "ahoj  ");

	key_action_ptr->execute(text);
	ASSERT_EQ(text, "ahoj   ");

	// console clean up
	for(int i = 4; i < text.length(); ++i){
		Term::cout << "\b \b" << std::flush;
	}
}

TEST_F(KeyActionTest, DefaultTest){
	std::string text = "";

	key_action_ptr = f.get_action(Term::Key::a);
	key_action_ptr->execute(text);
	ASSERT_EQ(text, "a");
	
	key_action_ptr = f.get_action(Term::Key::h);
	key_action_ptr->execute(text);
	ASSERT_EQ(text, "ah");
	
	key_action_ptr = f.get_action(Term::Key::o);	
	key_action_ptr->execute(text);
	ASSERT_EQ(text, "aho");
	
	key_action_ptr = f.get_action(Term::Key::j);
	key_action_ptr->execute(text);
	ASSERT_EQ(text, "ahoj");

	// console clean up
	for(int i = 0; i < text.length(); ++i){
		Term::cout << "\b \b" << std::flush;
	}
}

TEST_F(KeyActionTest, TabTest){
	std::string text = "tilt po";

	key_action_ptr = f.get_action(Term::Key::Tab);
	key_action_ptr->execute(text);
	ASSERT_EQ(text, "tilt position");

	// console clean up
	for(int i = 0; i < text.length(); ++i){
		Term::cout << "\b \b" << std::flush;
	}
}

TEST_F(KeyActionTest, EnterActionTest){
	key_action_ptr = f.get_action(Term::Key::Enter);
	std::string text = "ahoj";
	
	key_action_ptr->execute(text);
	
	// assert line was added to history
	ASSERT_EQ(h.get_previous(), "ahoj");

	// console clean up
	//for(int i = 0; i < 16; ++i){
	//	Term::cout << "\b \b" << std::flush;
	//}
}
