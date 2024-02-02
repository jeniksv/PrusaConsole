#include "cli.hpp"

cli::cli() : _running(true), _current_line(), _history(".prusa_console_history"), _tab(), _printer(), _key_action_factory(_history, _tab, _printer) {
	Term::terminal.setOptions(Term::Option::NoClearScreen, Term::Option::NoSignalKeys, Term::Option::Cursor, Term::Option::Raw);
	Term::Screen term_size{Term::screen_size()};
	Term::Cursor cursor{Term::cursor_position()};
}


void cli::reset_state(){
	Term::cout << "> " << std::flush;
	_history.reset();
	_current_line = "";
}


void cli::mainloop(){
	reset_state();

	while(_running){
		Term::Event event = Term::read_event();

		if(event.type() != Term::Event::Type::Key){
			continue;
		}

		Term::Key key(event);

		auto action = _key_action_factory.get_action(key);
		auto action_result = action->execute(_current_line);
	
		if(action_result == key_action_result::EXIT){
			_running = false;
		}
		
		if(action_result == key_action_result::CONTINUE_WITH_RESET){
			reset_state();
		}
	}
}
