#ifndef KEY_ACTIONS_H_
#define KEY_ACTIONS_H_

#include <memory>

#include "history.hpp"
#include "tab_completion.hpp"
#include "cpp-terminal/key.hpp"


class key_action_base{
public:
        virtual ~key_action_base();

        virtual void modify_current(std::string& current) = 0;
};


class key_action_factory{
public:
	key_action_factory(history& h, tab_completion& t);

	std::unique_ptr<key_action_base> get_action(const Term::Key& key_type);
private:
//	Term::Key _previous_key;
	history& _history_ref;
	tab_completion& _tab_ref;
};


class arrow_up_key_action : public key_action_base{
public:
	arrow_up_key_action(history& h);

	void modify_current(std::string& current) override;
private:
	history& _history_ref;
};


class arrow_down_key_action : public key_action_base{
public:
        arrow_down_key_action(history& h);

        void modify_current(std::string& current) override;
private:
	history& _history_ref;
};

/*
class arrow_left_key_action : public key_action_base{
public:
        arrow_left_key_action(history& h);

        void modify_current(std::string& current) override;
private:
	history& _history_ref;
};


class arrow_right_key_action : public key_action_base{
public:
        arrow_right_key_action(history& h);

        void modify_current(std::string& current) override;
private:
	history& _history_ref;
};
*/

class tab_action : public key_action_base{
public:
	tab_action(tab_completion& t); // TODO can be const?

	void modify_current(std::string& current) override;
private:
	tab_completion& _tab_ref;
};


class backspace_action : public key_action_base{
public:
	void modify_current(std::string& current) override;
};


class space_action : public key_action_base{
public:
	void modify_current(std::string& current) override;
};


class default_action : public key_action_base{
public:
	default_action(std::string k);

	void modify_current(std::string& current) override;
private:
	std::string _key_name;
};


class no_action : public key_action_base{
public:
	void modify_current(std::string& current) override;
};

#endif
