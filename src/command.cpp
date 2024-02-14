#include "command.hpp"

#include "cpp-terminal/iostream.hpp"

command::command(const std::string& _name, bool _leaf)
    : _name(_name)
    , _leaf(_leaf)
{
}

const std::string& command::get_name() const
{
    return _name;
}

bool command::is_leaf() const
{
    return _leaf;
}

bool command::starts_with(const std::string& prefix) const
{
    return std::equal(prefix.begin(), prefix.end(), _name.begin());
}

bool command_comparator::operator()(const command& lhs, const command& rhs) const
{
    return lhs.get_name() < rhs.get_name();
}

concrete_command_base::concrete_command_base(const std::string& name,
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : command(name, true)
    , _args_vector()
    , _proxies(_p)
{
}

void concrete_command_base::init_args_vector(std::stringstream& ss)
{
    _args_vector.clear();
    std::string temp;

    while (ss >> temp) {
        _args_vector.push_back(temp);
    }
}

std::string concrete_command_base::arguments()
{
    return std::string();
}

std::string concrete_command_base::help()
{
    return std::string("command has no help text");
}

composite_command::composite_command()
    : command("", false)
    , _children()
{
}

composite_command::composite_command(std::string _name)
    : command(_name, false)
    , _children()
{
}

void composite_command::add_command(std::shared_ptr<command> c)
{
    _children.push_back(c);
}

const std::vector<std::shared_ptr<command>>& composite_command::get_children() const
{
    return _children;
}

command_result composite_command::execute(std::stringstream& ss)
{
    std::string next;
    ss >> next;

    for (const auto& child : _children) {
        if (child->get_name() == next) {
            return child->execute(ss);
        }
    }

    return command_result::UNKNOWN_COMMAND;
}
