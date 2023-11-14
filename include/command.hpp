#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <algorithm>

// teoreticky tohle muze byt predek jenom, od kteryho budou dedit konkretni commandy
// TODO std::function for action ?
class command{
public:
	command(const std::string& name) : name(name) {}

	std::string name;

	void execute(); // TODO virtual? and then also virtual destructor

	bool starts_with(const std::string& prefix) const;
};

struct command_comparator{
	bool operator()(const command& lhs, const command& rhs) const;
};

#endif