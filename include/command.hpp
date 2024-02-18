#ifndef COMMAND_H_
#define COMMAND_H_

#include <dbus-cxx.h>

#include <algorithm>
#include <map>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

/**
 * @brief Enumeration representing the result of executing a command.
 */
enum class command_result {
    OK,
    INVALID_ARGUMENTS,
    UNKNOWN_COMMAND,
    NOT_IMPLEMENTED,
    EXIT,
    DBUS_ERROR,
    EXPOSURE_DOES_NOT_EXIST,
};

/**
 * @brief Base class for command objects.
 */
class command {
public:
    /**
     * @brief Constructor for the command class.
     *
     * @param name The name of the command.
     * @param leaf Flag indicating if the command is a leaf (non-composite) command.
     */
    command(const std::string& name, bool leaf);

    /**
     * @brief Virtual destructor for the command class.
     */
    virtual ~command() = default;

    /**
     * @brief Get the name of the command.
     *
     * @return The name of the command.
     */
    const std::string& get_name() const;

    /**
     * @brief Check if the command is a leaf (non-composite) command.
     *
     * @return True if the command is a leaf, false otherwise.
     */
    bool is_leaf() const;

    /**
     * @brief Check if the command name starts with a given prefix.
     *
     * @param prefix The prefix to check.
     * @return True if the command name starts with the prefix, false otherwise.
     */
    bool starts_with(const std::string& prefix) const;

    /**
     * @brief Execute the command with the provided arguments.
     *
     * @param args Stream containing command arguments.
     * @return Result of the command execution.
     */
    virtual command_result execute(std::stringstream& args) = 0;

protected:
    std::string _name;
    bool _leaf;
};

/**
 * @brief Base class for concrete (leaf) commands interacting with D-Bus.
 */
class concrete_command_base : public command {
public:
    /**
     * @brief Constructor for the concrete_command_base class.
     *
     * @param name The name of the command.
     * @param proxies Map of D-Bus object proxies used by the command.
     */
    concrete_command_base(const std::string& name, std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& proxies);

    /**
     * @brief Virtual destructor for the concrete_command_base class.
     */
    virtual ~concrete_command_base() = default;

    /**
     * @brief Execute the concrete command with the provided arguments.
     *
     * @param args Stream containing command arguments.
     * @return Result of the command execution.
     */
    virtual command_result execute(std::stringstream& args) = 0;

    /**
     * @brief Get a string representation of command arguments.
     *
     * @return String representation of command arguments.
     */
    virtual std::string arguments();

    /**
     * @brief Get help information for the command.
     *
     * @return Help information for the command.
     */
    virtual std::string help();

protected:
    std::map<std::string, std::shared_ptr<DBus::ObjectProxy>>& _proxies;
    std::vector<std::string> _args_vector;
};

/**
 * @brief Composite command class representing a collection of sub-commands.
 */
class composite_command : public command {
public:
    /**
     * @brief Default constructor for the composite_command class.
     */
    composite_command();

    /**
     * @brief Constructor for the composite_command class with a specified name.
     *
     * @param name The name of the composite command.
     */
    composite_command(std::string name);

    /**
     * @brief Add a sub-command to the composite command.
     *
     * @param child Shared pointer to the sub-command.
     */
    void add_command(std::shared_ptr<command> child);

    /**
     * @brief Get the vector of sub-commands.
     *
     * @return Vector of shared pointers to sub-commands.
     */
    const std::vector<std::shared_ptr<command>>& get_children() const;

    /**
     * @brief Execute the composite command with the provided arguments.
     *
     * @param args Stream containing command arguments.
     * @return Result of the command execution.
     */
    command_result execute(std::stringstream& args) override;

private:
    std::vector<std::shared_ptr<command>> _children;
};

/**
 * @brief Functor to compare two command objects.
 */
struct command_comparator {
    /**
     * @brief Compare two command objects.
     *
     * @param lhs First command object.
     * @param rhs Second command object.
     * @return True if the first command is less than the second, false otherwise.
     */
    bool operator()(const command& lhs, const command& rhs) const;
};
#endif
