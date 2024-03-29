#include "command_tree_builder.hpp"

command_tree_builder::command_tree_builder(std::shared_ptr<DBus::Connection> _connection, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies)
    : _root(std::make_shared<composite_command>())
    , _current_composite(_root)
    , _connection(_connection)
    , _proxies(_proxies)
{
}

command_tree_builder& command_tree_builder::add_concrete_command(std::shared_ptr<command> c)
{
    _current_composite->add_command(c);
    return *this;
}

command_tree_builder& command_tree_builder::add_composite_command(const std::string& name)
{
    auto c = std::make_shared<composite_command>(name);
    _current_composite->add_command(c);
    _composite_stack.push(_current_composite);
    _current_composite = c;
    return *this;
}

command_tree_builder& command_tree_builder::end_composite_command()
{
    _current_composite = _composite_stack.top();
    _composite_stack.pop();
    return *this;
}

command_tree command_tree_builder::build()
{
    return command_tree(_root);
}

command_tree_builder& command_tree_builder::add_core_commands()
{
    add_concrete_command(std::make_shared<help_command>("help", _root, _proxies));
    add_concrete_command(std::make_shared<exit_command>("exit", _proxies));
    return *this;
}

command_tree_builder& command_tree_builder::add_specific_commands()
{
    return *this;
}

command_tree tree_build_director::construct(command_tree_builder&& builder)
{
    return builder.add_core_commands().add_specific_commands().build();
}

mock_command_tree_builder::mock_command_tree_builder(
    std::shared_ptr<DBus::Connection> _connection,
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies)
    : command_tree_builder(_connection, _proxies)
{
}

command_tree_builder& mock_command_tree_builder::add_specific_commands()
{
    add_composite_command("tilt");
    add_composite_command("position");
    add_concrete_command(std::make_shared<default_command>("get", _proxies));
    add_concrete_command(std::make_shared<default_command>("set", _proxies));
    end_composite_command();
    end_composite_command();

    add_composite_command("tower");
    add_concrete_command(std::make_shared<default_command>("home", _proxies));
    add_composite_command("position");
    add_concrete_command(std::make_shared<default_command>("get", _proxies));
    add_concrete_command(std::make_shared<default_command>("set", _proxies));
    end_composite_command();
    end_composite_command();

    add_composite_command("pump");
    add_composite_command("position");
    add_concrete_command(std::make_shared<default_command>("get", _proxies));
    add_concrete_command(std::make_shared<default_command>("set", _proxies));
    end_composite_command();
    end_composite_command();

    add_composite_command("print");
    add_concrete_command(std::make_shared<default_command>("start", _proxies));
    add_concrete_command(std::make_shared<default_command>("stop", _proxies));
    end_composite_command();
    return *this;
}

slx_command_tree_builder::slx_command_tree_builder(
    std::shared_ptr<DBus::Connection> _connection,
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies)
    : command_tree_builder(_connection, _proxies)
{
}

command_tree_builder& slx_command_tree_builder::add_tilt()
{
    add_composite_command("tilt");
    add_concrete_command(std::make_shared<tilt_home_command>("home", _proxies));
    add_composite_command("position");
    add_concrete_command(std::make_shared<tilt_position_get_command>("get", _proxies));
    add_concrete_command(std::make_shared<tilt_position_set_command>("set", _proxies));
    end_composite_command();
    end_composite_command();
    return *this;
}

command_tree_builder& slx_command_tree_builder::add_tower()
{
    add_composite_command("tower");
    add_concrete_command(std::make_shared<tower_home_command>("home", _proxies));
    add_composite_command("position");
    add_concrete_command(std::make_shared<tower_position_get_command>("get", _proxies));
    add_concrete_command(std::make_shared<tower_position_set_command>("set", _proxies));
    end_composite_command();
    end_composite_command();
    return *this;
}

command_tree_builder& slx_command_tree_builder::add_resin_refill_system()
{
    add_composite_command("tank");
    add_concrete_command(std::make_shared<tank_fill_command>("fill", _proxies));
    add_concrete_command(std::make_shared<tank_empty_command>("empty", _proxies));
    end_composite_command();
    return *this;
}

command_tree_builder& slx_command_tree_builder::add_exposure_handlers()
{
    add_composite_command("print");
    add_concrete_command(std::make_shared<start_print_command>("start", _connection, _proxies));
    add_concrete_command(std::make_shared<stop_print_command>("stop", _connection, _proxies));
    end_composite_command();
    add_composite_command("exposure");
    add_concrete_command(std::make_shared<exposure_current_layer_command>("current_layer", _connection, _proxies));
    add_concrete_command(std::make_shared<exposure_time_remain_command>("time_remain", _connection, _proxies));
    add_concrete_command(std::make_shared<exposure_progress_command>("progress", _connection, _proxies));
    add_concrete_command(std::make_shared<exposure_resin_used_command>("resin_used", _connection, _proxies));
    end_composite_command();
    return *this;
}

sl2_command_tree_builder::sl2_command_tree_builder(
    std::shared_ptr<DBus::Connection> _connection,
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies)
    : slx_command_tree_builder(_connection, _proxies)
{
}

command_tree_builder& sl2_command_tree_builder::add_specific_commands()
{
    add_tilt();
    add_tower();
    add_exposure_handlers();
    add_resin_refill_system();
    return *this;
}

sl1s_command_tree_builder::sl1s_command_tree_builder(
    std::shared_ptr<DBus::Connection> _connection,
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies)
    : slx_command_tree_builder(_connection, _proxies)
{
}

command_tree_builder& sl1s_command_tree_builder::add_specific_commands()
{
    add_tilt();
    add_tower();
    add_exposure_handlers();
    return *this;
}
