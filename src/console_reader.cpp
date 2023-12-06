#include "console_reader.hpp"

console_reader::console_reader() : _history(".prusa_console_history"), _tab(), _key_action_factory(_history, _tab) {
	Term::terminal.setOptions(Term::Option::NoClearScreen, Term::Option::NoSignalKeys, Term::Option::Cursor, Term::Option::Raw);
	Term::Screen term_size{Term::screen_size()};
	Term::Cursor cursor{Term::cursor_position()};
}

void console_reader::clear_line(const std::string& s){
	for(int i=0; i < s.length(); ++i){
		Term::cout << "\b \b";
	}
}

void console_reader::write_line(const std::string& s){
	Term::cout << s << std::flush;
}

std::string console_reader::read_line(){
	std::string current;
	
	// TODO store previous states, history related
	while(true){
		Term::Event event = Term::read_event();

		if(event.type() != Term::Event::Type::Key){
			continue;
		}

		Term::Key key(event);

		// TODO tohle je necitelny jak svina, lip
		clear_line(current);
		_key_action_factory.get_action(key)->modify_current(current);
		write_line(current);

		// TODO chytrejsi by mozna bylo se koukat na posledni znak, jestli nahodou neni newline
		if(key == Term::Key::Enter){
			return current;
		}
		// TODO jak moc se lisi current a previous, podle toho napsat neco do konzole, ted je to stupid
	}	
}
