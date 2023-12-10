#include "key_actions.hpp"

key_action_base::~key_action_base(){}

key_action_factory::key_action_factory(history& h, tab_completion& t) : _history_ref(h), _tab_ref(t) {}

std::unique_ptr<key_action_base> key_action_factory::get_action(const Term::Key& key_type){
	if(key_type == Term::Key::ArrowLeft) return std::make_unique<no_action>();
	if(key_type == Term::Key::ArrowRight) return std::make_unique<no_action>();
	if(key_type == Term::Key::ArrowUp) return std::make_unique<arrow_up_key_action>(arrow_up_key_action(_history_ref));
	if(key_type == Term::Key::ArrowDown) return std::make_unique<arrow_down_key_action>(arrow_down_key_action(_history_ref));
	
	if(key_type == Term::Key::Backspace) return std::make_unique<backspace_action>();
	if(key_type == Term::Key::Space) return std::make_unique<space_action>();
	if(key_type == Term::Key::Tab) return std::make_unique<tab_action>(tab_action(_tab_ref, false));
	if(key_type == Term::Key::Enter) return std::make_unique<enter_action>(enter_action(_history_ref));

	if(key_type == Term::Key::Ctrl_C) return std::make_unique<ctrl_c_action>();
	// if(key_type == Term::key::) return std::make_unique<>();

	// TODO esc can return console state to default state
	// TODO Ctrl+R action
	return std::make_unique<default_action>(default_action(key_type.name()));
}


arrow_up_key_action::arrow_up_key_action(history& h) : _history_ref(h) {}

void arrow_up_key_action::execute(std::string& current){
	//current = _history_ref.get_current();
	//_history_ref.move_back();
	current = _history_ref.get_previous();
}

arrow_down_key_action::arrow_down_key_action(history& h) : _history_ref(h) {}

void arrow_down_key_action::execute(std::string& current){
	//_history_ref.move_next();
	//current = _history_ref.get_current();
	current = _history_ref.get_next();
}

void backspace_action::execute(std::string& current){
	current = current.empty() ? "" : current.substr(0, current.size() - 1);
}


tab_action::tab_action(tab_completion& _tab_ref, bool _double_tab) : _tab_ref(_tab_ref), _double_tab(_double_tab) {}

void tab_action::execute(std::string& current){
	// TODO if(_double_tab){}
	current = _tab_ref.get_path_match(current);
}

void space_action::execute(std::string& current){
	current.append(" ");
}


enter_action::enter_action(history& _history_ref) : _history_ref(_history_ref) {}

void enter_action::execute(std::string& current){
	_history_ref.add(current);
	current.append("\n");
}

void ctrl_c_action::execute(std::string& current){
	exit(0);
}


default_action::default_action(std::string k) : _key_name(k) {}

void default_action::execute(std::string& current){
	current.append(_key_name);
}


void no_action::execute(std::string& current){}
