#ifndef CONCRETE_COMMANDS_H_
#define CONCRETE_COMMANDS_H_

#include <dbus-cxx.h>

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

#include "command.hpp"
#include "cpp-terminal/iostream.hpp"
#include "cpp-terminal/key.hpp"

class exit_command : public concrete_command_base {
public:
    exit_command(std::string, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class help_command : public concrete_command_base {
public:
    help_command(std::string, std::shared_ptr<composite_command>,
        std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;

private:
    void print_help_tree(std::shared_ptr<command>, int);

    void print_indentation(int);

    std::shared_ptr<composite_command> _command_tree_root;
};

class tilt_home_command : public concrete_command_base {
public:
    tilt_home_command(std::string, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class tilt_position_get_command : public concrete_command_base {
public:
    tilt_position_get_command(std::string, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class tilt_position_set_command : public concrete_command_base {
public:
    tilt_position_set_command(std::string, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class default_command : public concrete_command_base {
public:
    default_command(std::string, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;
};

class tower_home_command : public concrete_command_base {
public:
    tower_home_command(std::string, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class tower_position_get_command : public concrete_command_base {
public:
    tower_position_get_command(std::string, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class tower_position_set_command : public concrete_command_base {
public:
    tower_position_set_command(std::string, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class tank_fill_command : public concrete_command_base {
public:
    tank_fill_command(std::string, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class tank_empty_command : public concrete_command_base {
public:
    tank_empty_command(std::string, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class exposure_command_base : public concrete_command_base {
public:
    exposure_command_base(std::string, std::shared_ptr<DBus::Connection>, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    virtual ~exposure_command_base() = default;

    virtual command_result execute(std::stringstream& args) = 0;

protected:
    bool set_current_exposure_object();

    std::shared_ptr<DBus::Connection> _connection;
};

class start_print_command : public concrete_command_base {
public:
    start_print_command(std::string, std::shared_ptr<DBus::Connection>, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

private:
    bool printer_in_available_state();

    bool set_current_exposure(const std::string&);

    bool wait_for_state_ready();

    std::shared_ptr<DBus::Connection> _connection;
};

class stop_print_command : public exposure_command_base {
public:
    stop_print_command(std::string, std::shared_ptr<DBus::Connection>, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

private:
    std::shared_ptr<DBus::Connection> _connection;
};

class exposure_current_layer_command : public exposure_command_base {
public:
    exposure_current_layer_command(std::string, std::shared_ptr<DBus::Connection>, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class exposure_time_remain_command : public exposure_command_base {
public:
    exposure_time_remain_command(std::string, std::shared_ptr<DBus::Connection>, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class exposure_progress_command : public exposure_command_base {
public:
    exposure_progress_command(std::string, std::shared_ptr<DBus::Connection>, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

class exposure_resin_used_command : public exposure_command_base {
public:
    exposure_resin_used_command(std::string, std::shared_ptr<DBus::Connection>, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_result execute(std::stringstream&) override;

    std::string help() override;
};

#endif
