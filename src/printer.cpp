#include "printer.hpp"

#include "cpp-terminal/iostream.hpp"

printer::printer()
    : _type(printer_model::UNKNOWN)
{
    init();
}

printer::printer(printer_model _type)
    : _type(_type)
{
    init();
}

void printer::connect_dbus()
{
    _dispatcher = DBus::StandaloneDispatcher::create();

    if (_dispatcher) {
        _connection = _dispatcher->create_connection(DBus::BusType::SYSTEM);
    }

    if (_connection) {
        _proxies.insert({ "cz.prusa3d.sl1.printer0", _connection->create_object_proxy("cz.prusa3d.sl1.printer0", "/cz/prusa3d/sl1/printer0") });
        _proxies.insert({ "cz.prusa3d.sl1.exposure0", _connection->create_object_proxy("cz.prusa3d.sl1.exposure0", "/cz/prusa3d/sl1/exposure0") });
    }
}

void printer::init()
{
    connect_dbus();

    if (_connection && _type == printer_model::UNKNOWN) {
        DBus::PropertyProxy<int>& printer_model_proxy = *(_proxies.at("cz.prusa3d.sl1.printer0")->create_property<int>("cz.prusa3d.sl1.printer0", "printer_model"));
        _type = static_cast<printer_model>(printer_model_proxy.value());
    }

    if (_type == printer_model::SL2) {
        _command_tree = tree_build_director().construct(sl2_command_tree_builder(_proxies));
    } else if (_type == printer_model::SL1S) {
    } else if (_type == printer_model::SL1) {
    } else {
        _command_tree = tree_build_director().construct(mock_command_tree_builder(_proxies));
    }
}

printer_model printer::get_type()
{
    return _type;
}

command_tree& printer::get_command_tree()
{
    return _command_tree;
}

command_result printer::dbus_request(const std::string& request)
{
    if (request.empty()) {
        return command_result::OK;
    }

    return _command_tree.execute_command(request);
}
