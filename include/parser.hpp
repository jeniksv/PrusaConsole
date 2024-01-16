#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <sstream>
#include <optional>

class command_parser{
public:
	command_parser();

	void process(const std::string&);
	
	std::optional<std::string> get_name() const;

	std::optional<std::vector<std::string>> get_arguments() const;
private:
	std::optional<std::string> _name;
	std::optional<std::vector<std::string>> _args;
};

#endif
