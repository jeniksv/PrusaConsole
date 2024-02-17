#ifndef COMMAND_TREE_BUILDER_H_
#define COMMAND_TREE_BUILDER_H_

#include <dbus-cxx.h>

#include <memory>
#include <string>

#include "command.hpp"
#include "command_tree.hpp"

/**
 * @brief Class for building command trees.
 *
 * The `command_tree_builder` class provides a fluent interface for constructing
 * hierarchical command trees. It supports the addition of concrete and composite
 * commands, building the tree, and adding specific commands.
 */
class command_tree_builder {
public:
    /**
     * @brief Default constructor for the command_tree_builder class.
     *
     * Initializes a command tree builder with an empty root.
     */
    command_tree_builder();

    /**
     * @brief Constructor for the command_tree_builder class with D-Bus proxies.
     *
     * Initializes a command tree builder with D-Bus proxies and an empty root.
     *
     * @param proxies Map of D-Bus object proxies used by commands.
     */
    command_tree_builder(std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& proxies);

    /**
     * @brief Virtual destructor for the command_tree_builder class.
     */
    virtual ~command_tree_builder() = default;

    /**
     * @brief Add a concrete command to the command tree.
     *
     * Adds a concrete command to the current composite command.
     *
     * @param command Shared pointer to the concrete command.
     * @return Reference to the command_tree_builder for method chaining.
     */
    command_tree_builder& add_concrete_command(std::shared_ptr<command> command);

    /**
     * @brief Add a composite command to the command tree.
     *
     * Adds a composite command with the specified name to the current composite command.
     *
     * @param name Name of the composite command.
     * @return Reference to the command_tree_builder for method chaining.
     */
    command_tree_builder& add_composite_command(const std::string& name);

    /**
     * @brief End the current composite command.
     *
     * Ends the current composite command and returns to its parent composite command.
     *
     * @return Reference to the command_tree_builder for method chaining.
     */
    command_tree_builder& end_composite_command();

    /**
     * @brief Add core commands to the command tree.
     *
     * Adds a set of core commands to the root of the command tree.
     *
     * @return Reference to the command_tree_builder for method chaining.
     */
    command_tree_builder& add_core_commands();

    /**
     * @brief Build the command tree.
     *
     * Builds and returns the command tree constructed by the builder.
     *
     * @return Command tree constructed by the builder.
     */
    command_tree build();

    /**
     * @brief Add specific commands to the command tree.
     *
     * Adds specific commands to the command tree. Override this method in derived
     * classes to add custom commands.
     *
     * @return Reference to the command_tree_builder for method chaining.
     */
    virtual command_tree_builder& add_specific_commands();

protected:
    std::shared_ptr<composite_command> _root;
    std::shared_ptr<composite_command> _current_composite;
    std::stack<std::shared_ptr<composite_command>> _composite_stack;
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies;
};

/**
 * @brief Class for directing the construction of command trees.
 *
 * The `tree_build_director` class is responsible for constructing command trees
 * using a command_tree_builder.
 */
class tree_build_director {
public:
    /**
     * @brief Construct a command tree using a command_tree_builder.
     *
     * Constructs and returns a command tree using the provided command_tree_builder.
     *
     * @param builder The command_tree_builder to use for constructing the tree.
     * @return Constructed command tree.
     */
    command_tree construct(command_tree_builder&& builder);
};

class mock_command_tree_builder : public command_tree_builder {
public:
    mock_command_tree_builder(std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_tree_builder& add_specific_commands() override;
};

class slx_command_tree_builder : public command_tree_builder {
public:
    slx_command_tree_builder(std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    virtual ~slx_command_tree_builder() = default;

    command_tree_builder& add_tilt();

    command_tree_builder& add_tower();

    command_tree_builder& add_resin_refill_system();

    command_tree_builder& add_exposure_handlers();
};

class sl2_command_tree_builder : public slx_command_tree_builder {
public:
    sl2_command_tree_builder(std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_tree_builder& add_specific_commands() override;
};

class sl1s_command_tree_builder : public slx_command_tree_builder {
public:
    sl1s_command_tree_builder(std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>&);

    command_tree_builder& add_specific_commands() override;
};

#endif
