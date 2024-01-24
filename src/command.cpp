#include "command.hpp"
#include "cpp-terminal/iostream.hpp"


command::command(const std::string& _name) : _name(_name) {}

command::~command() {}

std::string command::get_name() const{
	return _name;
}

bool command::starts_with(const std::string& prefix) const{
        return std::equal(prefix.begin(), prefix.end(), _name.begin());
}

command_result command::execute(const std::optional<std::vector<std::string>>& params){
	Term::cout << "DBUS action " << _name << "with arguments";
       	for(const std::string& s : params.value()) Term::cout << s << " ";
	Term::cout << std::endl;

	return command_result::OK;
}

void command::help(){
	Term::cout << "Commands has no help text." << std::endl;
}

bool command_comparator::operator()(const command& lhs, const command& rhs) const{
	return lhs.get_name() < rhs.get_name();
}
