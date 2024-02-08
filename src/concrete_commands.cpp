#include "concrete_commands.hpp"

exit_command::exit_command(std::string name, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies)
    : concrete_command_base(name, _proxies)
{
}

command_result exit_command::execute(std::stringstream& ss)
{
    init_args_vector(ss);

    if (!_args_vector.empty()) {
        return command_result::INVALID_ARGUMENTS;
    }

    return command_result::EXIT;
}

std::string exit_command::help()
{
    return "exits application";
}

help_command::help_command(std::string name, std::shared_ptr<composite_command> _command_tree_root,
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies)
    : concrete_command_base(name, _proxies)
    , _command_tree_root(_command_tree_root)
{
}

command_result help_command::execute(std::stringstream& ss)
{
    init_args_vector(ss);

    if (!_args_vector.empty()) {
        return command_result::INVALID_ARGUMENTS;
    }

    print_help_tree(_command_tree_root, 0);
    return command_result::OK;
}

void help_command::print_help_tree(std::shared_ptr<command> node, int depth)
{
    if (node->is_leaf()) {
        Term::cout << " -> " << std::dynamic_pointer_cast<concrete_command_base>(node)->help() << std::endl;
        return;
    }

    for (const auto& child : std::dynamic_pointer_cast<composite_command>(node)->get_children()) {
        print_indentation(depth);
        Term::cout << child->get_name();

        if (!child->is_leaf()) {
            Term::cout << std::endl;
        }

        print_help_tree(child, depth + 4);
    }
}

void help_command::print_indentation(int count)
{
    for (int i = 0; i < count; ++i) {
        Term::cout << " ";
    }

    Term::cout << std::flush;
}

std::string help_command::help()
{
    return "lists all commands and their usage";
}

tilt_home_command::tilt_home_command(std::string name, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : concrete_command_base(name, _p)
{
}

command_result tilt_home_command::execute(std::stringstream& ss)
{
    init_args_vector(ss);

    if (!_args_vector.empty()) {
        command_result::INVALID_ARGUMENTS;
    }

    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.at(interface)) {
        return command_result::DBUS_ERROR;
    }

    DBus::MethodProxy<void()>& tilt_home_proxy = *(_proxies.at(interface)->create_method<void()>(interface, "tilt_home"));
    tilt_home_proxy();

    return command_result::OK;
}

std::string tilt_home_command::help()
{
    return "move tilt to home position (position 0)";
}

tilt_position_get_command::tilt_position_get_command(std::string name,
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : concrete_command_base(name, _p)
{
}

command_result tilt_position_get_command::execute(std::stringstream& ss)
{
    init_args_vector(ss);

    if (!_args_vector.empty()) {
        command_result::INVALID_ARGUMENTS;
    }

    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.at(interface)) {
        return command_result::DBUS_ERROR;
    }

    DBus::PropertyProxy<int>& tilt_position_proxy = *(_proxies.at(interface)->create_property<int>(interface, "tilt_position"));
    Term::cout << tilt_position_proxy.value() << std::endl;
    return command_result::OK;
}

std::string tilt_position_get_command::help()
{
    return "returns tilt position (in microsteps)";
}

tilt_position_set_command::tilt_position_set_command(std::string name,
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : concrete_command_base(name, _p)
{
}

command_result tilt_position_set_command::execute(std::stringstream& ss)
{
    // TODO better value checks
    int value;
    ss >> value;

    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.at(interface)) {
        return command_result::DBUS_ERROR;
    }

    DBus::PropertyProxy<int>& tilt_position_proxy = *(_proxies.at("cz.prusa3d.sl1.printer0")->create_property<int>("cz.prusa3d.sl1.printer0", "tilt_position"));
    tilt_position_proxy.set_value(value);
    return command_result::OK;
}

std::string tilt_position_set_command::help()
{
    return "sets tilt position (in microsteps)";
}

default_command::default_command(std::string name, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies)
    : concrete_command_base(name, _proxies)
{
}

command_result default_command::execute(std::stringstream& ss)
{
    init_args_vector(ss);

    Term::cout << get_name() << " executed " << std::endl;

    for (const auto& arg : _args_vector) {
        Term::cout << arg << " ";
    }

    Term::cout << std::endl;

    return command_result::NOT_IMPLEMENTED;
}
