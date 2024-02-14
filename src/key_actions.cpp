#include "key_actions.hpp"

key_action_base::~key_action_base()
{
}

key_action_factory::key_action_factory(history& _history_ref, printer& _printer_ref)
    : _previous_key()
    , _history_ref(_history_ref)
    , _printer_ref(_printer_ref)
{
}

std::unique_ptr<key_action_base> key_action_factory::get_action(const Term::Key& key_type)
{
    std::unique_ptr<key_action_base> action;

    if (key_type == Term::Key::ArrowLeft) {
        action = std::make_unique<no_action>();
    } else if (key_type == Term::Key::ArrowRight) {
        action = std::make_unique<no_action>();
    } else if (key_type == Term::Key::ArrowUp) {
        action = std::make_unique<arrow_up_key_action>(arrow_up_key_action(_history_ref));
    } else if (key_type == Term::Key::ArrowDown) {
        action = std::make_unique<arrow_down_key_action>(arrow_down_key_action(_history_ref));
    } else if (key_type == Term::Key::Backspace) {
        action = std::make_unique<backspace_action>();
    } else if (key_type == Term::Key::Space) {
        action = std::make_unique<space_action>();
    } else if (key_type == Term::Key::Tab) {
        action = std::make_unique<tab_action>(_printer_ref.get_command_tree(), _previous_key == Term::Key::Tab);
    } else if (key_type == Term::Key::Enter) {
        action = std::make_unique<enter_action>(enter_action(_history_ref, _printer_ref));
    } else if (key_type == Term::Key::Ctrl_C) {
        action = std::make_unique<ctrl_c_action>();
    } else {
        action = std::make_unique<default_action>(default_action(key_type.name()));
    }

    _previous_key = key_type;

    return action;
}

arrow_up_key_action::arrow_up_key_action(history& h)
    : _history_ref(h)
{
}

key_action_result arrow_up_key_action::execute(std::string& current)
{
    for (int i = 0; i < current.length(); ++i) {
        Term::cout << "\b \b" << std::flush;
    }

    current = _history_ref.get_previous();

    Term::cout << current << std::flush;

    return key_action_result::CONTINUE;
}

arrow_down_key_action::arrow_down_key_action(history& h)
    : _history_ref(h)
{
}

key_action_result arrow_down_key_action::execute(std::string& current)
{
    for (int i = 0; i < current.length(); ++i) {
        Term::cout << "\b \b" << std::flush;
    }

    current = _history_ref.get_next();
    Term::cout << current << std::flush;

    return key_action_result::CONTINUE;
}

key_action_result backspace_action::execute(std::string& current)
{
    if (!current.empty()) {
        Term::cout << "\b \b" << std::flush;
    }

    current = current.empty() ? "" : current.substr(0, current.size() - 1);

    return key_action_result::CONTINUE;
}

tab_action::tab_action(command_tree& _tree_ref, bool _double_tab)
    : _tree_ref(_tree_ref)
    , _double_tab(_double_tab)
{
}

key_action_result tab_action::execute(std::string& current)
{
    if (_double_tab) {
        auto options = _tree_ref.get_complete_options(current);

        if (options.empty()) {
            return key_action_result::CONTINUE;
        }

        Term::cout << std::endl;

        for (const auto& options : options) {
            Term::cout << options << std::endl;
        }

        Term::cout << "> " << current << std::flush;
    } else {
        for (int i = 0; i < current.length(); ++i) {
            Term::cout << "\b \b" << std::flush;
        }

        _tree_ref.complete_command(current);

        Term::cout << current << std::flush;
    }

    return key_action_result::CONTINUE;
}

key_action_result space_action::execute(std::string& current)
{
    current.append(" ");
    Term::cout << " " << std::flush;

    return key_action_result::CONTINUE;
}

enter_action::enter_action(history& _history_ref, printer& _printer_ref)
    : _history_ref(_history_ref)
    , _printer_ref(_printer_ref)
{
}

key_action_result enter_action::execute(std::string& current)
{
    if (!current.empty()) {
        _history_ref.add(current);
    }

    Term::cout << std::endl;

    command_result result = _printer_ref.dbus_request(current);

    if (result == command_result::UNKNOWN_COMMAND) {
        Term::cout << "Unknown command" << std::endl;
    }

    if (result == command_result::INVALID_ARGUMENTS) {
        Term::cout << "Invalid arguments" << std::endl;
    }

    if (result == command_result::DBUS_ERROR) {
        Term::cout << "Dbus error" << std::endl;
        return key_action_result::EXIT;
    }

    return result == command_result::EXIT ? key_action_result::EXIT : key_action_result::CONTINUE_WITH_RESET;
}

key_action_result ctrl_c_action::execute(std::string& current)
{
    return key_action_result::EXIT;
}

default_action::default_action(std::string k)
    : _key_name(k)
{
}

key_action_result default_action::execute(std::string& current)
{
    current.append(_key_name);
    Term::cout << _key_name << std::flush;
    return key_action_result::CONTINUE;
}

key_action_result no_action::execute(std::string& current)
{
    return key_action_result::CONTINUE;
}
