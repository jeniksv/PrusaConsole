#include <vector>

#include "command.hpp"
#include "tab_completion.hpp"
#include "history.hpp"
#include "console_reader.hpp"


int main(int argc, char** argv){
	/*
	if(argc != 2){
		std::cout << "argument error" << std::endl;
		return 0;
	}
	*/

	console_reader reader;
	
	while(true){
		std::string line = reader.read_line();
		
		// TODO ted to nevadi ze tam je newline, bude se to parsovat do commandu, kde se stejne whitespacy zahodi
		if(line == "exit\n"){ break; }
		// command c = p.parse_line(line);
		// command.execute()
	}
}
