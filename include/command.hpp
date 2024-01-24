#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <vector>
#include <algorithm>
#include <optional>


enum class command_result{
	OK,
	INVALID_ARGUMENTS,
	UNKNOWN_COMMAND,
	NOT_IMPLEMENTED,
	EXIT,
};


class command{
public:
	command(const std::string&);

	virtual ~command();

	std::string get_name() const;

	bool starts_with(const std::string&) const;

	virtual command_result execute(const std::optional<std::vector<std::string>>&); // = 0; TODO make pure virtual, also vector can be const

	virtual void help();
protected:
	std::string _name;
};


struct command_comparator{
	bool operator()(const command&, const command&) const;
};

#endif
