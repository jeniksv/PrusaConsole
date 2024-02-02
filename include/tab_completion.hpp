#ifndef TAB_COMPLETION_H_
#define TAB_COMPLETION_H_

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <filesystem>

#include "command.hpp"


class tab_completion {
public:
	/*
	tab_completion();
	
	tab_completion(const std::set<std::string>&); // TODO get rid of ctor

        tab_completion(const std::set<command, command_comparator>&);

        void add_command(const command&);

	void remove_command(const command&);

        // returns longest common prefix
	// TODO these should be private and there should be one method ehich will decide if you are trying to
        std::string get_command_match(const std::string&);

        std::string get_path_match(const std::string&);

        std::vector<std::string> get_command_matches(const std::string&);
private:
	std::vector<std::string> get_commands_subset(const std::string&);

	std::string trim_prefix(const std::string&);

        std::string longest_common_prefix(std::vector<std::string>&);

        std::set<command, command_comparator> _commands;
	*/
};

#endif
