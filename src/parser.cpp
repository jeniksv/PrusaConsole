#include "parser.hpp"

command_parser::command_parser() : _name(), _args() {}

void command_parser::process(const std::string& line){
	std::istringstream stream(line);
	std::string temp_string;
	std::vector<std::string> temp_vector;

	stream >> temp_string;

	if(temp_string.empty()){
		_name = std::nullopt;
		_args = std::nullopt;
	} else {
		_name = temp_string;
		
		while(stream >> temp_string){
			temp_vector.push_back(temp_string);	
		}

		_args = !temp_vector.empty() ? std::make_optional(temp_vector) : std::nullopt;
	}
}

std::optional<std::string> command_parser::get_name() const{
	return _name;
}

std::optional<std::vector<std::string>> command_parser::get_arguments() const{
	return _args;
}

