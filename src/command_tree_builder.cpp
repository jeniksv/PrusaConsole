#include "command_tree_builder.hpp"

command_tree_builder::command_tree_builder() : _root(std::make_shared<composite_command>()), _current_composite(_root) {}

command_tree_builder& command_tree_builder::add_concrete_command(std::shared_ptr<command> c){
	_current_composite->add_command(c);
	return *this;
}

command_tree_builder& command_tree_builder::add_composite_command(const std::string& name){
	auto c = std::make_shared<composite_command>(name);
	_current_composite->add_command(c);
	_composite_stack.push(_current_composite);
	_current_composite = c;
	return *this;
}

command_tree_builder& command_tree_builder::end_composite_command(){
	_current_composite = _composite_stack.top();
	_composite_stack.pop();
	return *this;
}

command_tree command_tree_builder::build(){
	return command_tree(_root);
}

command_tree_builder& command_tree_builder::add_core_commands(){
	add_concrete_command(std::make_shared<help_command>("help", _root));
	add_concrete_command(std::make_shared<exit_command>("exit"));
	return *this;
}

command_tree_builder& command_tree_builder::add_specific_commands(){
	return *this;
}



command_tree tree_build_director::construct(command_tree_builder&& builder){
	return builder
		.add_core_commands()
		.add_specific_commands()
		.build();
}



slx_command_tree_builder::slx_command_tree_builder() : command_tree_builder() {}

command_tree_builder& slx_command_tree_builder::add_tilt(){
	add_composite_command("tilt");
		add_composite_command("position");
			add_concrete_command(std::make_shared<default_command>("get"));
			add_concrete_command(std::make_shared<default_command>("set"));
		end_composite_command();
	end_composite_command();
	return *this;
}

command_tree_builder& slx_command_tree_builder::add_tower(){
	add_composite_command("tower");
		add_composite_command("position");
			add_concrete_command(std::make_shared<default_command>("get"));
			add_concrete_command(std::make_shared<default_command>("set"));
		end_composite_command();
	end_composite_command();
	return *this;
}



sl2_command_tree_builder::sl2_command_tree_builder() : slx_command_tree_builder() {}

command_tree_builder& sl2_command_tree_builder::add_specific_commands(){
	add_tilt();
	add_tower();
	return *this;
}
