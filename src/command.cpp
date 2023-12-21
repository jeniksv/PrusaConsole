#include "command.hpp"
#include <iostream>

command::command(const std::string& _name) : _name(_name) {}

std::string command::get_name() const{
	return _name;
}

bool command::starts_with(const std::string& prefix) const{
        return std::equal(prefix.begin(), prefix.end(), _name.begin());
}

void command::execute(){
	std::cout << "DBUS action " << _name << std::endl;
}

void command::help(){
	std::cout << "Commands has no help text." << std::endl;
}


bool command_comparator::operator()(const command& lhs, const command& rhs) const{
	return lhs.get_name() < rhs.get_name();
}
