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

/**
 * @brief Enumeration representing different printer models.
 */
enum class printer_model {
    UNKNOWN = -1,
    MOCK = 0,
    SL1 = 1,
    SL1S = 2,
    M1 = 3,
    SL2 = 4,
};

/**
 * @brief Class representing a printer.
 *
 * The `printer` class is responsible for managing communication with a printer,
 * handling D-Bus requests, and providing access to a command tree.
 */
class printer {
public:
    /**
     * @brief Default constructor for the printer class.
     *
     * Initializes a printer with the unknown model.
     */
    printer();

    /**
     * @brief Constructor for the printer class with a specified printer model.
     *
     * Initializes a printer with the specified model.
     *
     * @param type The printer model.
     */
    printer(printer_model type);

    /**
     * @brief Get the printer model.
     *
     * @return The printer model.
     */
    printer_model get_type();

    /**
     * @brief Send a D-Bus request to the printer.
     *
     * Sends a D-Bus request to the printer based on the provided command.
     *
     * @param command The D-Bus command to be sent.
     * @return Result of the D-Bus request.
     */
    command_result dbus_request(const std::string& command);

    /**
     * @brief Get the command tree associated with the printer.
     *
     * @return Reference to the command tree associated with the printer.
     */
    command_tree& get_command_tree();

private:
    /**
     * @brief Connect to the D-Bus for printer communication.
     */
    void connect_dbus();

    /**
     * @brief Initialize the printer.
     */
    void init();

    std::shared_ptr<DBus::Dispatcher> _dispatcher;
    std::shared_ptr<DBus::Connection> _connection;
    // TODO create new object dbus_proxies
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>> _proxies;

    printer_model _type;
    command_tree _command_tree;
};

#endif
