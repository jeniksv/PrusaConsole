#include "command.hpp"
#include <iostream>


command::command(const std::string& _name) : _name(_name) {}

command::~command() {}

std::string command::get_name() const{
	return _name;
}

bool command::starts_with(const std::string& prefix) const{
        return std::equal(prefix.begin(), prefix.end(), _name.begin());
}

command_result command::execute(const std::optional<std::vector<std::string>>& params){
	std::cout << "DBUS action " << _name << "with arguments";
       	for(const std::string& s : params.value()) std::cout << s << " ";
	std::cout << std::endl;

	return command_result::OK;
}

void command::help(){
	std::cout << "Commands has no help text." << std::endl;
}

bool command_comparator::operator()(const command& lhs, const command& rhs) const{
	return lhs.get_name() < rhs.get_name();
}



help_command::help_command(std::string name) : command(name) {}

command_result help_command::execute(const std::optional<std::vector<std::string>>& args){
	if(args){
		return command_result::INVALID_ARGUMENTS;
	}
	
	std::cout << "help_command execute" << std::endl;
	return command_result::OK;
}

void help_command::help(){
	std::cout << "lists all commands and their usage" << std::endl;
}


exit_command::exit_command(std::string name) : command(name) {}

command_result exit_command::execute(const std::optional<std::vector<std::string>>& args){
	if(args){
		return command_result::INVALID_ARGUMENTS;	
	}

	std::cout << "exit_command execute" << std::endl;
	return command_result::OK;
}

void exit_command::help(){
	std::cout << "exits application" << std::endl;
}

default_command::default_command(std::string name) : command(name) {}

command_result default_command::execute(const std::optional<std::vector<std::string>>& args){
	std::cout << get_name() << " executed" << std::endl;
	return command_result::NOT_IMPLEMENTED;	
}
