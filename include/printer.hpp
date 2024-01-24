#ifndef PRINTER_H_
#define PRINTER_H_

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>

#include "command.hpp"
#include "concrete_commands.hpp"


// printer is defined by name and set of commands
// you can extended to ask via dbus for name at start of the app, so you dont need app arguments
class printer{
public:
	printer();
	
	printer(const std::string&);

	std::string get_type();

	bool valid_command(const std::string&);

	std::unique_ptr<command>& get_command(const std::string&); 
private:
	void add_command(const std::string&, std::unique_ptr<command>);

	void build(const std::string&);
	
	std::string _type;
	std::map<std::string, std::unique_ptr<command>> _commands;

	friend class help_command;
};

#endif
