#include "printer.hpp"
#include "printer0Proxy.h"
#include "cpp-terminal/iostream.hpp"

printer::printer() : _type() {
	init();
}

printer::printer(const std::string& _type) : _type(_type) {
	init();
}

void printer::init(){
	std::shared_ptr<DBus::Dispatcher> dispatcher = DBus::StandaloneDispatcher::create();
	std::shared_ptr<DBus::Connection> connection = dispatcher->create_connection( DBus::BusType::SYSTEM );
	std::shared_ptr<DBus::ObjectProxy> object = connection->create_object_proxy("cz.prusa3d.sl1.printer0", "/cz/prusa3d/sl1/printer0");
	DBus::MethodProxy<void()>& add_proxy = *(object->create_method<void()>("cz.prusa3d.sl1.printer0","tilt_home"));
	DBus::PropertyProxy<int>& printer_model_proxy = *(object->create_property<int>("cz.prusa3d.sl1.printer0", "printer_model"));
	add_proxy();
	
	if(_type.empty()){
		Term::cout << printer_model_proxy.value() << std::endl;
	}

	_type = "sl2";
	//std::unique_ptr

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
