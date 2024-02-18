#include "concrete_commands.hpp"

exit_command::exit_command(std::string name, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies)
    : concrete_command_base(name, _proxies)
{
}

command_result exit_command::execute(std::stringstream& ss)
{
    if (!ss.eof()) {
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
    if (!ss.eof()) {
        return command_result::INVALID_ARGUMENTS;
    }

    print_help_tree(_command_tree_root, 0);
    return command_result::OK;
}

void help_command::print_help_tree(std::shared_ptr<command> node, int depth)
{
    if (node->is_leaf()) {
        auto concrete_node = std::dynamic_pointer_cast<concrete_command_base>(node);

        if (!concrete_node->arguments().empty()) {
            Term::cout << " " << concrete_node->arguments() << std::flush;
        }

        Term::cout << " -> " << concrete_node->help() << std::endl;
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
    if (!ss.eof()) {
        command_result::INVALID_ARGUMENTS;
    }

    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.contains(interface) || !_proxies.at(interface)) {
        return command_result::DBUS_ERROR;
    }

    DBus::MethodProxy<void()>& tilt_home_proxy = *(_proxies.at(interface)->create_method<void()>(interface, "tilt_home"));
    tilt_home_proxy();

    return command_result::OK;
}

std::string tilt_home_command::help()
{
    return "sets tilt position to home position (0 microsteps)";
}

tilt_position_get_command::tilt_position_get_command(std::string name,
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : concrete_command_base(name, _p)
{
}

command_result tilt_position_get_command::execute(std::stringstream& ss)
{
    if (!ss.eof()) {
        return command_result::INVALID_ARGUMENTS;
    }

    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.contains(interface) || !_proxies.at(interface)) {
        return command_result::DBUS_ERROR;
    }

    auto position_proxy = this->_proxies.at(interface)->create_property<int>(interface, "tilt_position", DBus::PropertyAccess::ReadWrite, DBus::PropertyUpdateType::DoesNotUpdate);
    Term::cout << position_proxy->value() << std::endl;
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
    int value;
    ss >> value;

    if (ss.fail()) {
        return command_result::INVALID_ARGUMENTS;
    }

    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.contains(interface) || !_proxies.at(interface)) {
        return command_result::DBUS_ERROR;
    }

    auto position_proxy = this->_proxies.at(interface)->create_property<int>(interface, "tilt_position", DBus::PropertyAccess::ReadWrite, DBus::PropertyUpdateType::DoesNotUpdate);
    position_proxy->set_value(value);
    return command_result::OK;
}

std::string tilt_position_set_command::help()
{
    return "sets tilt position to given position (in microsteps)";
}

default_command::default_command(std::string name, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies)
    : concrete_command_base(name, _proxies)
{
}

command_result default_command::execute(std::stringstream& ss)
{
    return command_result::NOT_IMPLEMENTED;
}

tower_home_command::tower_home_command(std::string name, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : concrete_command_base(name, _p)
{
}

command_result tower_home_command::execute(std::stringstream& ss)
{
    if (!ss.eof()) {
        command_result::INVALID_ARGUMENTS;
    }

    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.contains(interface) || !_proxies.at(interface)) {
        return command_result::DBUS_ERROR;
    }

    DBus::MethodProxy<void()>& tower_home_proxy = *(_proxies.at(interface)->create_method<void()>(interface, "tower_home"));
    tower_home_proxy();

    return command_result::OK;
}

std::string tower_home_command::help()
{
    return "sets tower position to home position (0 microsteps)";
}

tower_position_get_command::tower_position_get_command(std::string name,
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : concrete_command_base(name, _p)
{
}

command_result tower_position_get_command::execute(std::stringstream& ss)
{
    if (!ss.eof()) {
        return command_result::INVALID_ARGUMENTS;
    }

    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.contains(interface) || !_proxies.at(interface)) {
        return command_result::DBUS_ERROR;
    }

    auto position_proxy = this->_proxies.at(interface)->create_property<int>(interface, "tower_position_nm", DBus::PropertyAccess::ReadWrite, DBus::PropertyUpdateType::DoesNotUpdate);
    Term::cout << position_proxy->value() << std::endl;
    return command_result::OK;
}

std::string tower_position_get_command::help()
{
    return "returns tower position (in nanometers)";
}

tower_position_set_command::tower_position_set_command(std::string name,
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : concrete_command_base(name, _p)
{
}

command_result tower_position_set_command::execute(std::stringstream& ss)
{
    int value;
    ss >> value;

    if (ss.fail()) {
        return command_result::INVALID_ARGUMENTS;
    }

    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.contains(interface) || !_proxies.at(interface)) {
        return command_result::DBUS_ERROR;
    }

    auto position_proxy = this->_proxies.at(interface)->create_property<int>(interface, "tower_position_nm", DBus::PropertyAccess::ReadWrite, DBus::PropertyUpdateType::DoesNotUpdate);
    position_proxy->set_value(value);
    return command_result::OK;
}

std::string tower_position_set_command::help()
{
    return "sets tower position to given position (in microsteps)";
}

tank_fill_command::tank_fill_command(std::string name, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : concrete_command_base(name, _p)
{
}

command_result tank_fill_command::execute(std::stringstream& ss)
{
    if (!ss.eof()) {
        command_result::INVALID_ARGUMENTS;
    }

    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.contains(interface) || !_proxies.at(interface)) {
        return command_result::DBUS_ERROR;
    }

    DBus::MethodProxy<void()>& tank_fill_proxy = *(_proxies.at(interface)->create_method<void()>(interface, "fill_tank"));
    tank_fill_proxy();

    return command_result::OK;
}

std::string tank_fill_command::help()
{
    return "starts resin tank autofill";
}

tank_empty_command::tank_empty_command(std::string name, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : concrete_command_base(name, _p)
{
}

command_result tank_empty_command::execute(std::stringstream& ss)
{
    if (!ss.eof()) {
        command_result::INVALID_ARGUMENTS;
    }

    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.contains(interface) || !_proxies.at(interface)) {
        return command_result::DBUS_ERROR;
    }

    DBus::MethodProxy<void()>& tank_empty_proxy = *(_proxies.at(interface)->create_method<void()>(interface, "empty_tank"));
    tank_empty_proxy();

    return command_result::OK;
}

std::string tank_empty_command::help()
{
    return "starts to empty resin tank";
}

exposure_command_base::exposure_command_base(std::string name, std::shared_ptr<DBus::Connection> _c, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : concrete_command_base(name, _p)
    , _connection(_c)
{
}

bool exposure_command_base::set_current_exposure_object()
{
    std::string interface = "cz.prusa3d.sl1.printer0";

    if (!_proxies.contains(interface)) {
        return false;
    }

    try {
        auto exposure_proxy = this->_proxies.at(interface)->create_property<DBus::Path>(interface, "current_exposure", DBus::PropertyAccess::ReadWrite, DBus::PropertyUpdateType::DoesNotUpdate);
        std::string current_exposure_path;

        for (const auto& item : exposure_proxy->value().decomposed()) {
            current_exposure_path.append("/");
            current_exposure_path.append(item);
        }

        if (current_exposure_path == "/") {
            return false;
        }

        interface = "cz.prusa3d.sl1.exposure0";
        this->_proxies[interface] = _connection->create_object_proxy(interface, current_exposure_path);
    } catch (...) {
        return false;
    }
    return true;
}

start_print_command::start_print_command(std::string name, std::shared_ptr<DBus::Connection> _c, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : concrete_command_base(name, _p)
    , _connection(_c)
{
}

bool start_print_command::printer_in_available_state()
{
    std::string interface = "cz.prusa3d.sl1.printer0";
    auto state_proxy = this->_proxies.at(interface)->create_property<int>(interface, "state", DBus::PropertyAccess::ReadWrite, DBus::PropertyUpdateType::DoesNotUpdate);
    return state_proxy->value() == 1;
}

bool start_print_command::set_current_exposure(const std::string& project_name)
{
    std::string interface = "cz.prusa3d.sl1.printer0";
    auto& print_proxy = *(_proxies.at(interface)->create_method<DBus::Path(std::string, bool)>(interface, "print"));

    std::string current_exposure_path;

    try {
        auto object_path = print_proxy(project_name, true);

        for (const auto& item : object_path.decomposed()) {
            current_exposure_path.append("/");
            current_exposure_path.append(item);
        }
    } catch (...) {
        return false;
    }

    interface = "cz.prusa3d.sl1.exposure0";
    this->_proxies[interface] = _connection->create_object_proxy(interface, current_exposure_path);
    return true;
}

bool start_print_command::wait_for_state_ready()
{
    std::string interface = "cz.prusa3d.sl1.exposure0";
    auto proxy = this->_proxies.at(interface)->create_property<int>(interface, "state", DBus::PropertyAccess::ReadWrite, DBus::PropertyUpdateType::DoesNotUpdate);

    auto t_end = std::chrono::system_clock::now() + std::chrono::seconds(20);

    while (std::chrono::system_clock::now() < t_end) {
        if (proxy->value() == 26) {
            return true;
        }
    }

    return false;
}

command_result start_print_command::execute(std::stringstream& ss)
{
    std::string project_name;

    ss >> project_name;

    if (ss.fail()) {
        return command_result::INVALID_ARGUMENTS;
    }

    if (!std::filesystem::exists(project_name)) {
        return command_result::INVALID_ARGUMENTS;
    }

    if (!printer_in_available_state()) {
        Term::cout << "Printer not available in state" << std::endl;
        return command_result::OK;
    }

    if (!set_current_exposure(project_name)) {
        Term::cout << "Invalid project" << std::endl;
        return command_result::OK;
    }

    if (!wait_for_state_ready()) {
        Term::cout << "Printer not in available state" << std::endl;
        return command_result::OK;
    }

    std::string interface = "cz.prusa3d.sl1.exposure0";
    DBus::MethodProxy<void()>& confirm_start = *(_proxies.at(interface)->create_method<void()>(interface, "confirm_resin_in"));
    confirm_start();

    return command_result::OK;
}

stop_print_command::stop_print_command(std::string name, std::shared_ptr<DBus::Connection> _c, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : exposure_command_base(name, _c, _p)
{
}

command_result stop_print_command::execute(std::stringstream& ss)
{
    std::string interface = "cz.prusa3d.sl1.exposure0";

    if (!set_current_exposure_object()) {
        return command_result::EXPOSURE_DOES_NOT_EXIST;
    }

    DBus::MethodProxy<void()>& cancel_proxy = *(_proxies.at(interface)->create_method<void()>(interface, "cancel"));
    cancel_proxy();

    return command_result::OK;
}

exposure_current_layer_command::exposure_current_layer_command(std::string name, std::shared_ptr<DBus::Connection> _c, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : exposure_command_base(name, _c, _p)
{
}

command_result exposure_current_layer_command::execute(std::stringstream& ss)
{
    std::string interface = "cz.prusa3d.sl1.exposure0";

    if (!set_current_exposure_object()) {
        return command_result::EXPOSURE_DOES_NOT_EXIST;
    }

    auto proxy = this->_proxies.at(interface)->create_property<int>(interface, "current_layer", DBus::PropertyAccess::ReadWrite, DBus::PropertyUpdateType::DoesNotUpdate);
    Term::cout << proxy->value() << std::endl;
    return command_result::OK;
}

std::string exposure_current_layer_command::help()
{
    return "returns the number of the currently printed layer";
}

exposure_time_remain_command::exposure_time_remain_command(std::string name, std::shared_ptr<DBus::Connection> _c, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : exposure_command_base(name, _c, _p)
{
}

command_result exposure_time_remain_command::execute(std::stringstream& ss)
{
    std::string interface = "cz.prusa3d.sl1.exposure0";

    if (!set_current_exposure_object()) {
        return command_result::EXPOSURE_DOES_NOT_EXIST;
    }

    auto proxy = this->_proxies.at(interface)->create_property<int>(interface, "time_remain_ms", DBus::PropertyAccess::ReadWrite, DBus::PropertyUpdateType::DoesNotUpdate);
    float time = proxy->value() / 1000;
    Term::cout << time << std::endl;
    return command_result::OK;
}

std::string exposure_time_remain_command::help()
{
    return "returns print remaining time in seconds";
}

exposure_progress_command::exposure_progress_command(std::string name, std::shared_ptr<DBus::Connection> _c, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : exposure_command_base(name, _c, _p)
{
}

command_result exposure_progress_command::execute(std::stringstream& ss)
{
    std::string interface = "cz.prusa3d.sl1.exposure0";

    if (!set_current_exposure_object()) {
        return command_result::EXPOSURE_DOES_NOT_EXIST;
    }

    auto proxy = this->_proxies.at(interface)->create_property<double>(interface, "progress", DBus::PropertyAccess::ReadWrite, DBus::PropertyUpdateType::DoesNotUpdate);

    Term::cout << proxy->value() << "%" << std::endl;
    return command_result::OK;
}

std::string exposure_progress_command::help()
{
    return "returns print progress in percentage";
}

exposure_resin_used_command::exposure_resin_used_command(std::string name, std::shared_ptr<DBus::Connection> _c, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _p)
    : exposure_command_base(name, _c, _p)
{
}

command_result exposure_resin_used_command::execute(std::stringstream& ss)
{
    std::string interface = "cz.prusa3d.sl1.exposure0";

    if (!set_current_exposure_object()) {
        return command_result::EXPOSURE_DOES_NOT_EXIST;
    }

    auto proxy = this->_proxies.at(interface)->create_property<double>(interface, "resin_used_ml", DBus::PropertyAccess::ReadWrite, DBus::PropertyUpdateType::DoesNotUpdate);

    Term::cout << proxy->value() << std::endl;
    return command_result::OK;
}

std::string exposure_resin_used_command::help()
{
    return "returns resin_used in milliliters";
}
