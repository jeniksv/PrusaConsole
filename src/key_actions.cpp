#include "key_actions.hpp"

key_action_base::~key_action_base(){}

key_action_factory::key_action_factory(history& _history_ref, tab_completion& _tab_ref, printer& _printer_ref, command_parser& _parser_ref) :
	_history_ref(_history_ref),
	_tab_ref(_tab_ref),
	_printer_ref(_printer_ref),
	_parser_ref(_parser_ref) {}

std::unique_ptr<key_action_base> key_action_factory::get_action(const Term::Key& key_type){
	if(key_type == Term::Key::ArrowLeft) return std::make_unique<no_action>();
	if(key_type == Term::Key::ArrowRight) return std::make_unique<no_action>();
	if(key_type == Term::Key::ArrowUp) return std::make_unique<arrow_up_key_action>(arrow_up_key_action(_history_ref));
	if(key_type == Term::Key::ArrowDown) return std::make_unique<arrow_down_key_action>(arrow_down_key_action(_history_ref));
	
	if(key_type == Term::Key::Backspace) return std::make_unique<backspace_action>();
	if(key_type == Term::Key::Space) return std::make_unique<space_action>();
	if(key_type == Term::Key::Tab) return std::make_unique<tab_action>(tab_action(_tab_ref, false));
	if(key_type == Term::Key::Enter) return std::make_unique<enter_action>(enter_action(_history_ref, _printer_ref, _parser_ref));

	if(key_type == Term::Key::Ctrl_C) return std::make_unique<ctrl_c_action>();

	return std::make_unique<default_action>(default_action(key_type.name()));
}


arrow_up_key_action::arrow_up_key_action(history& h) : _history_ref(h) {}

key_action_result arrow_up_key_action::execute(std::string& current){
	current = _history_ref.get_previous();
	return key_action_result::OK;
}


arrow_down_key_action::arrow_down_key_action(history& h) : _history_ref(h) {}

key_action_result arrow_down_key_action::execute(std::string& current){
	current = _history_ref.get_next();
	return key_action_result::OK;
}


key_action_result backspace_action::execute(std::string& current){
	current = current.empty() ? "" : current.substr(0, current.size() - 1);
	return key_action_result::OK;
}


tab_action::tab_action(tab_completion& _tab_ref, bool _double_tab) : _tab_ref(_tab_ref), _double_tab(_double_tab) {}

key_action_result tab_action::execute(std::string& current){
	current = _tab_ref.get_path_match(current);
	return key_action_result::OK;
}


key_action_result space_action::execute(std::string& current){
	current.append(" ");
	return key_action_result::OK;
}


enter_action::enter_action(history& _history_ref, printer& _printer_ref, command_parser& _parser_ref) :
	_history_ref(_history_ref),
	_printer_ref(_printer_ref),
	_parser_ref(_parser_ref) {}

key_action_result enter_action::execute(std::string& current){
	if(!current.empty()){
		_history_ref.add(current);
	}
	current.append("\n");
	return key_action_result::COMMAND_READY;
	/*
	_parser_ref.process(current);

	if(!_parser_ref.get_name().has_value()){
		return key_action_result::RESET;
	}

	_history_ref.add(current);

	if(!_printer_ref.valid_command(_parser_ref.get_name().value())){
		return key_action_result::RESET; // TODO invalid command
	}

	// rename to get_command
	auto& dbus_request = _printer_ref.get_action(_parser_ref.get_name().value());
	auto result = dbus_request->execute(_parser_ref.get_arguments());

	return result == command_result::EXIT ? key_action_result::EXIT : key_action_result::RESET; // TODO when exit_command -> return EXIT
	*/
}


key_action_result ctrl_c_action::execute(std::string& current){
	// TODO invalid pointers
	return key_action_result::EXIT;
}


default_action::default_action(std::string k) : _key_name(k) {}

key_action_result default_action::execute(std::string& current){
	current.append(_key_name);
	return key_action_result::OK;
}


key_action_result no_action::execute(std::string& current){
	return key_action_result::OK;
}
