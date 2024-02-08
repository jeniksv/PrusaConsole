#ifndef CONCRETE_COMMANDS_H_
#define CONCRETE_COMMANDS_H_

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <dbus-cxx.h>

#include "command.hpp"
#include "cpp-terminal/key.hpp"
#include "cpp-terminal/iostream.hpp"


class exit_command : public concrete_command_base{
public:
	exit_command(std::string);

	command_result execute(std::stringstream&) override;

	std::string help() override;
};


class help_command : public concrete_command_base{
public:
	help_command(std::string, std::shared_ptr<composite_command>);

	command_result execute(std::stringstream&) override;

	std::string help() override;
private:
	void print_help_tree(std::shared_ptr<command>, int);

	void print_indentation(int);

	std::shared_ptr<composite_command> _command_tree_root;
};


class start_print_command : public concrete_command_base{
public:
	command_result execute(std::stringstream&) override;
};


class stop_print_command : public concrete_command_base{
public:
	command_result execute(std::stringstream&) override;
};


class tilt_home_command : public concrete_command_base{
public:
	tilt_home_command(std::string, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

	command_result execute(std::stringstream&) override;

	std::string help() override;
private:
	std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies;
};


class default_command : public concrete_command_base{
public:
	default_command(std::string);

	command_result execute(std::stringstream&) override;
};

#endif
