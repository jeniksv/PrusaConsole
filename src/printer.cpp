#include "printer.hpp"
#include "cpp-terminal/iostream.hpp"


printer::printer() : _type() {
	init();
}

printer::printer(const std::string& _type) : _type(_type) {
	init();
}

void printer::init(){
	if(_type.empty()){
		_type = "sl2"; // TODO ask via dbus
	}

	if(_type == "sl2"){
		_command_tree = tree_build_director().construct(sl2_command_tree_builder());
	} else if(_type == "mock"){
		_command_tree = tree_build_director().construct(mock_command_tree_builder());
	}
}

std::string printer::get_type(){
	return _type;
}

command_tree& printer::get_command_tree(){
	return _command_tree;
}

command_result printer::dbus_request(const std::string& request){
	if(request.empty()){
		return command_result::OK;
	}

	return _command_tree.execute_command(request);
}
