#ifndef PRINTER_H_
#define PRINTER_H_

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "command.hpp"


// printer is defined by set of commands
class printer{
public:
	// teoreticky by to slo i tak, ze se v ctoru bude volat printer_factory
	printer(const std::string&);

	// void add_command(const std::unique_ptr<command>);

	// std::unique_ptr<command> get_command(const std::string&);
	// API bude get_command()->execute(std::vector<std::string> params);
private:
	// TODO factory bude friend
	// TODO switch to map
	std::vector<std::unique_ptr<command>> _commands;
};

class printer_factory{
public:
	static std::unique_ptr<printer_base> get_printer_type(const std::string&);
	
	void init_printer(const std::string& name){
		if(name == "--sl2"){
			
		}
	
	}

private:

};

/*
class sla_printer : public printer_base{
};

class fdm_printer : public printer_base{
};

class sl1 : public sla_printer{
};

class sl2 : public sla_printer{
};
*/

#endif
