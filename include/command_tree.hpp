#ifndef COMMAND_TREE_H_
#define COMMAND_TREE_H_

#include <set>
#include <memory>
#include <vector>
#include <tuple>
#include <filesystem>

#include "command.hpp"
#include "concrete_commands.hpp"


class command_tree{
public:
	command_tree();

	command_tree(std::shared_ptr<command>);

	void complete_command(std::string&);	

	std::vector<std::string> get_complete_options(const std::string&);

	command_result execute_command(const std::string&);
private:
	void complete_composite_command(const std::shared_ptr<composite_command>, std::string&, const std::string&);

	void complete_path(std::string&, const std::string&);

	std::vector<std::string> get_composite_command_options(const std::shared_ptr<composite_command>, const std::string&);

	std::vector<std::string> get_path_options(const std::string&);

	std::tuple<std::shared_ptr<command>, std::string> get_parsed_tree_path(const std::string&);

	std::string longest_common_prefix(const std::set<std::string>&);


	std::shared_ptr<command> _root;
};


#endif
