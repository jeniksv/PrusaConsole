#include "command.hpp"
#include <iostream>

bool command::starts_with(const std::string& prefix) const{
        return std::equal(prefix.begin(), prefix.end(), name.begin());
}

void command::execute(){
	std::cout << "DBUS action " << name << std::endl;
}

bool command_comparator::operator()(const command& lhs, const command& rhs) const{
	return lhs.name < rhs.name;
}
