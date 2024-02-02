#include "concrete_commands.hpp"

exit_command::exit_command(std::string name) : concrete_command_base(name) {}

command_result exit_command::execute(std::stringstream& ss){
	init_args_vector(ss);

	if(!_args_vector.empty()){
		return command_result::INVALID_ARGUMENTS;
	}

	return command_result::EXIT;
}

std::string exit_command::help(){
	return "exits application";
}


help_command::help_command(std::string name, std::shared_ptr<composite_command> _command_tree_root) :
	concrete_command_base(name),
	_command_tree_root(_command_tree_root) {}

command_result help_command::execute(std::stringstream& ss){
	init_args_vector(ss);
	
	if(!_args_vector.empty()){
		return command_result::INVALID_ARGUMENTS;
	}

	print_help_tree(_command_tree_root, 0);
	return command_result::OK;
}

void help_command::print_help_tree(std::shared_ptr<command> node, int depth){
	if(node->is_leaf()){
		Term::cout << " -> " << std::dynamic_pointer_cast<concrete_command_base>(node)->help() << std::endl;
		return;
	}

	for(const auto& child : std::dynamic_pointer_cast<composite_command>(node)->get_children()){
		print_indentation(depth);
		Term::cout << child->get_name();
		
		if(!child->is_leaf()){
			Term::cout << std::endl;	
		}

		print_help_tree(child, depth + 4);
	}
}

void help_command::print_indentation(int count){
	for(int i = 0; i < count; ++i){
		Term::cout << " ";
	}

	Term::cout << std::flush;
}


std::string help_command::help(){
	return "lists all commands and their usage";
}



default_command::default_command(std::string name) : concrete_command_base(name) {}

command_result default_command::execute(std::stringstream& ss){
	init_args_vector(ss);

	Term::cout << get_name() << " executed " << std::endl;

	for(const auto& arg : _args_vector){
		Term::cout << arg << " ";	
	}

	Term::cout << std::endl;

	return command_result::NOT_IMPLEMENTED;
}
