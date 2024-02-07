#ifndef COMMAND_TREE_BUILDER_H_
#define COMMAND_TREE_BUILDER_H_

#include <string>
#include <memory>
#include <dbus-cxx.h>

#include "command.hpp"
#include "command_tree.hpp"


class command_tree_builder{
public:
	command_tree_builder();

	command_tree_builder(std::shared_ptr<DBus::Connection>);

	virtual ~command_tree_builder() = default;

	command_tree_builder& add_concrete_command(std::shared_ptr<command>);

	command_tree_builder& add_composite_command(const std::string&);

	command_tree_builder& end_composite_command();

	command_tree_builder& add_core_commands();

	command_tree build();

	virtual command_tree_builder& add_specific_commands();
protected:
	std::shared_ptr<composite_command> _root;
	std::shared_ptr<composite_command> _current_composite;
	std::stack<std::shared_ptr<composite_command>> _composite_stack;
	std::shared_ptr<DBus::Connection> _dbus_connection;
	std::shared_ptr<DBus::ObjectProxy> _printer0_ptr;
};


class tree_build_director{
public:
	command_tree construct(command_tree_builder&&);
};


class mock_command_tree_builder : public command_tree_builder{
public:
	mock_command_tree_builder();

	command_tree_builder& add_specific_commands() override;
};

class slx_command_tree_builder : public command_tree_builder{
public:
	slx_command_tree_builder(std::shared_ptr<DBus::Connection>);

	virtual ~slx_command_tree_builder() = default;

	command_tree_builder& add_tilt();

	command_tree_builder& add_tower();
};


class sl2_command_tree_builder : public slx_command_tree_builder{
public:
	sl2_command_tree_builder(std::shared_ptr<DBus::Connection>);

	command_tree_builder& add_specific_commands() override;
};


#endif
