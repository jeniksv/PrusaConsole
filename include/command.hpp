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


class exit_command : public command{
public:
	exit_command();

	command_result execute(const std::optional<std::vector<std::string>>&) override;

	void help() override;
};


// muze byt friend na printer class aby vedel o vsech commandech
class help_command : public command{
public:
	help_command();

	command_result execute(const std::optional<std::vector<std::string>>&) override;

	void help() override;
};


class start_print_command : public command{
public:
	command_result execute(const std::optional<std::vector<std::string>>&) override;	
};


class stop_print_command : public command{
public:
	command_result execute(const std::optional<std::vector<std::string>>&) override;
};

#endif
