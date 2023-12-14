#ifndef PRINTER_H_
#define PRINTER_H_

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "command.hpp"

class printer_base{
public:
	void add_command(const std::unique_ptr<command>);
protected:
	std::vector<std::unique_ptr<command>> _commands;
};

class printer_factory{
pulibc:
	std::unique_ptr<printer_base> get_printer_type(const std::string&);
};

class sla_printer : public printer_base{
};

class fdm_printer : public printer_base{
};

class sl1 : sla_printer : public printer_base{
};

class sl2 : sla_printer : public printer_base{
};

#endif
