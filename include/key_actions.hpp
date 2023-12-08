#ifndef KEY_ACTIONS_H_
#define KEY_ACTIONS_H_

#include <memory>

#include "history.hpp"
#include "tab_completion.hpp"
#include "cpp-terminal/key.hpp"


class key_action_base{
public:
        virtual ~key_action_base();

        virtual void execute(std::string&) = 0;
};


class key_action_factory{
public:
	key_action_factory(history&, tab_completion&);

	std::unique_ptr<key_action_base> get_action(const Term::Key&);
private:
	// Term::Key _previous_key;
	history& _history_ref;
	tab_completion& _tab_ref;
};


class arrow_up_key_action : public key_action_base{
public:
	arrow_up_key_action(history&);

	void execute(std::string&) override;
private:
	history& _history_ref;
};


class arrow_down_key_action : public key_action_base{
public:
        arrow_down_key_action(history&);

        void execute(std::string&) override;
private:
	history& _history_ref;
};

/*
class arrow_left_key_action : public key_action_base{
public:
        arrow_left_key_action(history&);

        void execute(std::string&) override;
private:
	history& _history_ref;
};


class arrow_right_key_action : public key_action_base{
public:
        arrow_right_key_action(history&);

        void execute(std::string&) override;
private:
	history& _history_ref;
};
*/

class tab_action : public key_action_base{
public:
	tab_action(tab_completion&, bool); // TODO can be const?

	void execute(std::string&) override;
private:
	tab_completion& _tab_ref;

	bool _double_tab;
};


class backspace_action : public key_action_base{
public:
	void execute(std::string&) override;
};


class space_action : public key_action_base{
public:
	void execute(std::string&) override;
};


class enter_action : public key_action_base{
public:
	enter_action(history&);

	void execute(std::string&) override;
private:
	history& _history_ref;
};


class ctrl_c_action : public key_action_base{
public:
	void execute(std::string&) override;
};


class default_action : public key_action_base{
public:
	default_action(std::string);

	void execute(std::string&) override;
private:
	std::string _key_name;
};


class no_action : public key_action_base{
public:
	void execute(std::string&) override;
};

#endif
