#ifndef KEY_ACTIONS_H_
#define KEY_ACTIONS_H_

#include "history.hpp"
#include "tab_completion.hpp"


// action functions modify
class key_action_base{
public:
        virtual ~key_action_base();

	// TODO return type maybe should be std::string because of scope
        virtual std::string modify_current(const std::string& current);
};

/* TODO tohle vyres potom, ted potrebujes aspon uz nacitat ten vstup
class key_action_factory{
public:
	std::unique_ptr<key_action_base> get_action(Term::Key key_type){
		if(tab ...)
	
	}
};
*/

// TODO chci vytvorit spesl tridu pro kazdou klavesu? -> JO
// ARROW KEY UP
// TODO update last in history
class arrow_up_key_action : public key_action_base{
public:
	arrow_up_key_action(std::shared_ptr<history> h_ptr);

	std::string modify_current(const std::string& current) override;
private:
	std::shared_ptr<history> _history_ptr;
};

class arrow_down_key_action : public key_action_base{
public:
        arrow_down_key_action(std::shared_ptr<history> h_ptr);

        std::string modify_current(const std::string& current) override;
private:
        std::shared_ptr<history> _history_ptr;
};

/*
class arrow_left_key_action : public key_action_base{
public:
        arrow_left_key_action(std::shared_ptr<history> h_ptr);

        std::string modify_current(const std::string& current) override;
private:
        std::shared_ptr<history> _history_ptr;
};

class arrow_right_key_action : public key_action_base{
public:
        arrow_right_key_action(std::shared_ptr<history> h_ptr);

        std::string modify_current(const std::string& current) override;
private:
        std::shared_ptr<history> _history_ptr;
};
*/




class tab_action : public key_action_base{
public:
	tab_action(const tab_completion& t);

	std::string modify_current(const std::string& current) override;
};

class backspace_action : public key_action_base{
public:
	std::string modify_current(const std::string& current) override;
};

class enter_action : public key_action_base{
public:
	std::string modify_current(const std::string& current) override;
};

#endif