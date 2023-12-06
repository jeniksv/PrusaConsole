#ifndef TAB_COMPLETION_H_
#define TAB_COMPLETION_H_

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <filesystem>

#include "command.hpp"

// TODO more complex -> each command should have specified aruments, which can be completed
class tab_completion {
public:
	tab_completion();
	// TODO get rid of
	tab_completion(const std::set<std::string>& commands);

        tab_completion(const std::set<command, command_comparator>& commands);

        void add_command(const command& name);

	void remove_command(const command& name);

        // returns longest common prefix
	// TODO these should be private and there should be one method ehich will decide if you are trying to
        std::string get_command_match(const std::string& prefix); //, const std::vector<std::string>& commands);

        std::string get_path_match(const std::string& prefix);

        std::vector<std::string> get_command_matches(const std::string& prefix);
private:
	std::vector<std::string> get_commands_subset(const std::string& prefix);

	std::string trim_prefix(const std::string& prefix);

        std::string longest_common_prefix(const std::vector<std::string>& commands);

        std::set<command, command_comparator> _commands;
};

#endif
