#ifndef KEY_ACTIONS_H_
#define KEY_ACTIONS_H_

#include <memory>

#include "history.hpp"
#include "printer.hpp"
#include "command.hpp"
#include "cpp-terminal/key.hpp"
#include "cpp-terminal/iostream.hpp"


enum class key_action_result{
	CONTINUE,
	CONTINUE_WITH_RESET,
	EXIT,
};


class key_action_base{
public:
        virtual ~key_action_base();

        virtual key_action_result execute(std::string&) = 0;
};


class key_action_factory{
public:
	key_action_factory(history&, printer&);

	std::unique_ptr<key_action_base> get_action(const Term::Key&);

	void reset();
private:
	Term::Key _previous_key;
	history& _history_ref;
	printer& _printer_ref;
};


class arrow_up_key_action : public key_action_base{
public:
	arrow_up_key_action(history&);

	key_action_result execute(std::string&) override;
private:
	history& _history_ref;
};


class arrow_down_key_action : public key_action_base{
public:
        arrow_down_key_action(history&);

        key_action_result execute(std::string&) override;
private:
	history& _history_ref;
};

/*
class arrow_left_key_action : public key_action_base{
public:
        arrow_left_key_action(history&);

        key_action_result execute(std::string&) override;
private:
	history& _history_ref;
};


class arrow_right_key_action : public key_action_base{
public:
        arrow_right_key_action(history&);

        key_action_result execute(std::string&) override;
private:
	history& _history_ref;
};
*/

class tab_action : public key_action_base{
public:
	tab_action(command_tree&, bool);

	key_action_result execute(std::string&) override;
private:
	command_tree& _tree_ref;
	bool _double_tab;
};


class backspace_action : public key_action_base{
public:
	key_action_result execute(std::string&) override;
};


class space_action : public key_action_base{
public:
	key_action_result execute(std::string&) override;
};


class enter_action : public key_action_base{
public:
	enter_action(history&, printer&);

	key_action_result execute(std::string&) override;
private:
	history& _history_ref;
	printer& _printer_ref;
};


class ctrl_c_action : public key_action_base{
public:
	key_action_result execute(std::string&) override;
};


class default_action : public key_action_base{
public:
	default_action(std::string);

	key_action_result execute(std::string&) override;
private:
	std::string _key_name;
};


class no_action : public key_action_base{
public:
	key_action_result execute(std::string&) override;
};

#endif
