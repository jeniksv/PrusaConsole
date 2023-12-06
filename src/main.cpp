#include "command.hpp"
#include "tab_completion.hpp"
#include "history.hpp"
#include "console_reader.hpp"


int main(){
	//try{
	console_reader c;
	while(true){
		std::string line = c.read_line();
		
		if(line == "exit"){
			break;
		}

		std::cout << line << std::endl;
	}
	//} catch(...){}
}

/*
#include "cpp-terminal/cursor.hpp"
#include "cpp-terminal/exception.hpp"
#include "cpp-terminal/input.hpp"
#include "cpp-terminal/iostream.hpp"
#include "cpp-terminal/key.hpp"
#include "cpp-terminal/options.hpp"
#include "cpp-terminal/screen.hpp"
#include "cpp-terminal/terminal.hpp"
#include "cpp-terminal/tty.hpp"
#include "cpp-terminal/version.hpp"
#include <string>
#include <iostream>

int main(){
        Term::terminal.setOptions(Term::Option::NoClearScreen, Term::Option::NoSignalKeys, Term::Option::Cursor, Term::Option::Raw);
        Term::Cursor cursor{Term::cursor_position()};
        Term::Screen term_size{Term::screen_size()};

        int current_length = 0;

        Term::cout << "> " << std::flush;

        while(true){
                Term::Event event = Term::read_event();

  	              if(event.type() != Term::Event::Type::Key){
                        continue;
                }

                Term::Key key(event); // TODO zbavit se Term::Key za Term::Event::Type::Key::Enter

                if(key == Term::Key::Backspace){
                        if(current_length > 0) Term::cout << "\b \b" << std::flush;
                        current_length -= current_length > 0 ? 1 : 0;
                        continue;
                }

                if(key == Term::Key::Enter){
                        Term::cout << std::endl;
                        break;
                        //return current;
                }

                current_length++;
                // TODO space action
                if(key == Term::Key::Space){
                        Term::cout << " " << std::flush;
                        continue;
                }

                Term::cout << key.name() << std::flush;
                // TODO
        }
}*/
