#include "key_actions.hpp"
#include "cpp-terminal/key.hpp"

std::unique_ptr<key_action_base> key_action_factory::get_action(const Term::Key& key_type){
	if(key_type == Term::Key::Tab) return std::make_unique< tab >();

	if(key_type == Term::Key::ArrowLeft) return std::make_unique< space >();
	if(key_type == Term::key::ArrowRight) return std::make_unique<>();
	if(key_type == Term::key::ArrowUp) return std::make_unique<>();
	if(key_type == Term::key::ArrowDown) return std::make_unique<>();
	
	if(key_type == Term::key::Backspace) return std::make_unique<>();
	if(key_type == Term::key::Space) return std::make_unique<>();
	if(key_type == Term::key::) return std::make_unique<>();

	// TODO esc can return console state to default state

	return std::make_unique< default_action >();
}
