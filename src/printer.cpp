#include "printer.hpp"
#include "cpp-terminal/iostream.hpp"

printer::printer() : _type(printer_model::UNKNOWN) {
	init();
}

printer::printer(printer_model _type) : _type(_type) {
	init();
}

void printer::init(){
	//std::shared_ptr<DBus::Dispatcher> dispatcher = DBus::StandaloneDispatcher::create();
	//std::shared_ptr<DBus::Connection> connection = dispatcher->create_connection( DBus::BusType::SYSTEM );
	dispatcher = DBus::StandaloneDispatcher::create();
	connection = dispatcher->create_connection( DBus::BusType::SYSTEM );
	// TODO pass pritner0 directly and return ptr to it
	object = connection->create_object_proxy("cz.prusa3d.sl1.printer0", "/cz/prusa3d/sl1/printer0");
	if(_type == printer_model::UNKNOWN){
		DBus::PropertyProxy<int>& printer_model_proxy = *(object->create_property<int>("cz.prusa3d.sl1.printer0", "printer_model"));
		// Term::cout << printer_model_proxy.value() << std::endl;

		_type = static_cast<printer_model>(printer_model_proxy.value());
	}

	if(_type == printer_model::SL2){
		_command_tree = tree_build_director().construct(sl2_command_tree_builder(object));
	} else {
		_command_tree = tree_build_director().construct(mock_command_tree_builder());
	}
}

printer_model printer::get_type(){
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
