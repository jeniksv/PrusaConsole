#ifndef PRINTER_H_
#define PRINTER_H_

#include <dbus-cxx.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "command.hpp"
#include "command_tree.hpp"
#include "command_tree_builder.hpp"
#include "concrete_commands.hpp"

enum class printer_model {
    UNKNOWN = -1,
    MOCK = 0,
    SL1 = 1,
    SL1S = 2,
    M1 = 3,
    SL2 = 4,
};

class printer {
public:
    printer();

    printer(printer_model);

    printer_model get_type();

    command_result dbus_request(const std::string&);

    command_tree& get_command_tree();

private:
    void connect_dbus();

    void init();

    std::shared_ptr<DBus::Dispatcher> _dispatcher;
    std::shared_ptr<DBus::Connection> _connection;
    std::shared_ptr<DBus::ObjectProxy> object;

    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>> _proxies;

    printer_model _type;
    command_tree _command_tree;
};

#endif
