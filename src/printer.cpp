#include "printer.hpp"
#include "command.hpp"

std::unique_ptr<printer_base> printer_factory::get_printer_type(const std::string& printer_name){
	if(printer_name == "--sl1"){
		sl1 printer;
		printer.add_command();
		printer.add_command();
	}
	
	if(printer_name == "--sl2"){
		sl2 printer;
		printer.add_command(std::make_unique<>());
		//printer.add_command();
		return std::make_unique<>();
	}
}
