#include "command.hpp"
#include "tab_completion.hpp"
#include "history.hpp"
#include "console_reader.hpp"


int main(){
	//try{
	console_reader c;
	while(true){
		std::string line = c.read_line();
		//for(char c : line){ std::cout << c << std::endl; }	
		
		// TODO ted to nevadi ze tam je newline, bude se to parsovat do commandu, kde se stejne whitespacy zahodi
		if(line == "exit\n"){ break; }
		// command c = p.parse_line(line);
		// dbus_action d(command);
		// d.execute(); ... neco takovyho
		// dbus_processor.execute(command); or c.execute()


		// std::cout << line << std::endl;
	}
	//} catch(...){}
}
