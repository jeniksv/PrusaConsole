#include "concrete_commands.hpp"

help_command::help_command(std::string name) : command(name) {}

command_result help_command::execute(const std::optional<std::vector<std::string>>& args){
	if(args){
		return command_result::INVALID_ARGUMENTS;
	}

	Term::cout << "help_command execute" << std::endl;
	return command_result::OK;
}

void help_command::help(){
	Term::cout << "lists all commands and their usage" << std::endl;
}


exit_command::exit_command(std::string name) : command(name) {}

command_result exit_command::execute(const std::optional<std::vector<std::string>>& args){
	if(args){
		return command_result::INVALID_ARGUMENTS;
	}

	// Term::cout << "exit_command execute" << std::endl;
	return command_result::EXIT;
}

void exit_command::help(){
	Term::cout << "exits application" << std::endl;
}


default_command::default_command(std::string name) : command(name) {}

command_result default_command::execute(const std::optional<std::vector<std::string>>& args){
	Term::cout << get_name() << " executed" << std::endl;
	return command_result::NOT_IMPLEMENTED;
}

