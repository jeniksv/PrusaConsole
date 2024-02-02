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


class command_tree_builder{
public:
        command_tree_builder();

        command_tree_builder& add_concrete_command(std::shared_ptr<command>);

        command_tree_builder& add_composite_command(const std::string&);

        command_tree_builder& end_composite_command();

	command_tree_builder& add_core_commands();

	command_tree_builder& add_core_slx();

	command_tree build();
protected:
        std::shared_ptr<composite_command> _root;
        std::shared_ptr<composite_command> _current_composite;
        std::stack<std::shared_ptr<composite_command>> _composite_stack;
};


#endif
