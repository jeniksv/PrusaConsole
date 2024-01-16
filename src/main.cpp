#include <string>
#include <optional>

#include "command.hpp"
#include "tab_completion.hpp"
#include "history.hpp"
#include "console_reader.hpp"
#include "printer.hpp"
#include "parser.hpp"


int main(int argc, char** argv){
	printer p;

	console_reader reader;
	command_parser parser;
	
	while(true){
		std::string line = reader.read_line();
		
		parser.process(line);

		if(!parser.get_name().has_value()){
			continue;
		}
		
		if(!p.valid_command(parser.get_name().value())){
			Term::cout << "Invalid command" << std::endl;
			continue;
		}

		// TODO get rid of =, this should be handled by exit_command
		if(parser.get_name() == "exit"){
			break;
		}
		
		auto& action = p.get_action(parser.get_name().value());
		auto& result = action->execute(parser.get_arguments());

		//Term::cout << result << std::endl;
	}
}
