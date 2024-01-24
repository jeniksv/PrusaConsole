#include "cli.hpp"

cli::cli() : _running(true), _current_line(), _history(".prusa_console_history"), _tab(), _printer(), _parser(), _key_action_factory(_running, _history, _tab, _printer, _parser) {
	Term::terminal.setOptions(Term::Option::NoClearScreen, Term::Option::NoSignalKeys, Term::Option::Cursor, Term::Option::Raw);
	Term::Screen term_size{Term::screen_size()};
	Term::Cursor cursor{Term::cursor_position()};
}


void cli::show_prompt(){
	Term::cout << "> " << std::flush;
}


void cli::clear_line(const std::string& s){
	for(int i=0; i < s.length(); ++i){
		Term::cout << "\b \b";
	}
}


void cli::write_line(const std::string& s){
	Term::cout << s << std::flush;
}


void cli::reset_state(){
	show_prompt();
	_history.reset();
	_current_line = "";
}


void cli::process_command(){
	_parser.process(_current_line);

	if(!_parser.get_name().has_value() || !_printer.valid_command(_parser.get_name().value())){
		reset_state();
		return;
	}

	auto& dbus_request = _printer.get_action(_parser.get_name().value());
	auto result = dbus_request->execute(_parser.get_arguments());

	// TODO pochytat vsechno chyby z commandu

	_running = result == command_result::EXIT;
	reset_state();
}


void cli::mainloop(){
	show_prompt();
	
	while(_running){
		Term::Event event = Term::read_event();

		if(event.type() != Term::Event::Type::Key){
			continue;
		}

		Term::Key key(event);

		auto action = _key_action_factory.get_action(key);
		auto action_result = action->execute(_current_line);
	
		if(action_result == key_action_result::COMMAND_READY){
			process_command();
		}
	}
}
