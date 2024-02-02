#ifndef PRINTER_H_
#define PRINTER_H_

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>

#include "command.hpp"
#include "command_tree.hpp"
#include "concrete_commands.hpp"


class printer{
public:
	printer();
	
	std::string get_type();

	command_result dbus_request(const std::string&);

	command_tree& get_command_tree();
private:
	void build(const std::string&);

	void build_sl2();
	
	std::string _type;
	command_tree _command_tree;

	friend class help_command;
};

#endif
