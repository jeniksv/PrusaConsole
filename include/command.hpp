#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <algorithm>

// teoreticky tohle muze byt predek jenom, od kteryho budou dedit konkretni commandy
// TODO std::function for action ?

enum class dbus_action {
	START_PRINT,
	STOP_PRINT,
};


// command_base
class command{
public:
	command(const std::string& name) : name(name) {}

	// TODO getter and setter methods
	std::string name;

	void execute(); // TODO virtual? and then also virtual destructor

	bool starts_with(const std::string& prefix) const;
};

// TODO command factory

struct command_comparator{
	bool operator()(const command& lhs, const command& rhs) const;
};

/*
class print_start_command(){
public:
	
}
*/

#endif
