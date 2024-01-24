#ifndef CONCRETE_COMMANDS_H_
#define CONCRETE_COMMANDS_H_

#include <string>
#include <vector>
#include <algorithm>
#include <optional>

#include "command.hpp"
#include "cpp-terminal/key.hpp"
#include "cpp-terminal/iostream.hpp"


class exit_command : public command{
public:
	exit_command(std::string);

	command_result execute(const std::optional<std::vector<std::string>>&) override;

	void help() override;
};


class help_command : public command{
public:
	help_command(std::string);

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


class default_command : public command{
public:
	default_command(std::string);

	command_result execute(const std::optional<std::vector<std::string>>&) override;
};

#endif
