#ifndef KEY_ACTIONS_H_
#define KEY_ACTIONS_H_

#include <memory>

#include "command.hpp"
#include "cpp-terminal/iostream.hpp"
#include "cpp-terminal/key.hpp"
#include "history.hpp"
#include "printer.hpp"

/**
 * @brief Enumeration representing the result of a key action.
 */
enum class key_action_result {
    CONTINUE,
    CONTINUE_WITH_RESET,
    EXIT,
};

/**
 * @brief Base class for key actions.
 *
 * The `key_action_base` class provides an interface for key actions.
 */
class key_action_base {
public:
    /**
     * @brief Virtual destructor for the key_action_base class.
     */
    virtual ~key_action_base();

    /**
     * @brief Execute the key action.
     *
     * @param input The input string to be modified by the action.
     * @return Result of executing the key action.
     */
    virtual key_action_result execute(std::string& input) = 0;
};

/**
 * @brief Class for creating key actions.
 *
 * The `key_action_factory` class creates key actions based on the provided key events.
 */
class key_action_factory {
public:
    /**
     * @brief Constructor for the key_action_factory class.
     *
     * @param history_ref Reference to the history object.
     * @param printer_ref Reference to the printer object.
     */
    key_action_factory(history& history_ref, printer& printer_ref);

    /**
     * @brief Get a unique pointer to a key action based on the provided key event.
     *
     * @param key The key event for which to create an action.
     * @return Unique pointer to the created key action.
     */
    std::unique_ptr<key_action_base> get_action(const Term::Key& key);

    /**
     * @brief Reset the key action factory.
     */
    void reset();

private:
    Term::Key _previous_key;
    history& _history_ref;
    printer& _printer_ref;
};

class arrow_up_key_action : public key_action_base {
public:
    arrow_up_key_action(history&);

    key_action_result execute(std::string&) override;

private:
    history& _history_ref;
};

class arrow_down_key_action : public key_action_base {
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

class tab_action : public key_action_base {
public:
    tab_action(command_tree&, bool);

    key_action_result execute(std::string&) override;

private:
    command_tree& _tree_ref;
    bool _double_tab;
};

class backspace_action : public key_action_base {
public:
    key_action_result execute(std::string&) override;
};

class space_action : public key_action_base {
public:
    key_action_result execute(std::string&) override;
};

class enter_action : public key_action_base {
public:
    enter_action(history&, printer&);

    key_action_result execute(std::string&) override;

private:
    history& _history_ref;
    printer& _printer_ref;
};

class ctrl_c_action : public key_action_base {
public:
    key_action_result execute(std::string&) override;
};

class default_action : public key_action_base {
public:
    default_action(std::string);

    key_action_result execute(std::string&) override;

private:
    std::string _key_name;
};

class no_action : public key_action_base {
public:
    key_action_result execute(std::string&) override;
};

#endif
