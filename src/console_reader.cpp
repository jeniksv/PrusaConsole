#include "console_reader.hpp"
/*
std::string console_reader::read_line(){
	std::string current;

	while(true){
		Term::Event event = Term::read_event();
		
		if(event.type() != Term::Event::Type::Key){
			continue;
		}

		Term::Key key(event); // TODO zbavit se Term::Key za Term::Event::Type::Key::Enter

		if(key == Term::Key::Enter){
			return current;
		}
		// TODO
	}	
}
*/
