#include "printer.hpp"
#include "command.hpp"
#include "cpp-terminal/iostream.hpp"


printer::printer() : _type("sl2"), _commands() {
	build(_type);
}


printer::printer(const std::string& printer_type) : _type(printer_type), _commands(){
	build(_type);
}


std::string printer::get_type(){
	return _type;
}


bool printer::valid_command(const std::string& command){
	return _commands.find(command) != _commands.end();
}


std::unique_ptr<command>& printer::get_action(const std::string& command){
	//return _commands.find(command)->second;
	auto itr = _commands.find(command);

	if(itr != _commands.end()){
		return itr->second;
	}

	throw std::out_of_range("command " + command + " not found.");
}


void printer::add_command(const std::string& name, std::unique_ptr<command> object_ptr){
	_commands[name] = std::move(object_ptr);
}


void printer::build(const std::string& printer_type){
	if(printer_type == "sl1"){
		return;
	}
	
	if(printer_type == "sl2"){
		add_command("help", std::move(std::make_unique<help_command>()));
		add_command("exit", std::move(std::make_unique<exit_command>()));
		return;
	}

	if(printer_type == "manhattan"){
		return;
	}

	// throw std::invalid_argument("Printer " + printer_type + " not supported.");
}
