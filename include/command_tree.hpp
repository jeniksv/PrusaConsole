#ifndef COMMAND_TREE_H_
#define COMMAND_TREE_H_

#include <filesystem>
#include <memory>
#include <set>
#include <tuple>
#include <vector>

#include "command.hpp"
#include "concrete_commands.hpp"

/**
 * @brief Class representing a command tree structure.
 *
 * The `command_tree` class is responsible for managing and executing commands
 * organized in a hierarchical tree structure.
 */
class command_tree {
public:
    /**
     * @brief Default constructor for the command_tree class.
     *
     * Initializes an empty command tree.
     */
    command_tree();

    /**
     * @brief Constructor for the command_tree class with a specified root command.
     *
     * Initializes the command tree with the given root command.
     *
     * @param root Shared pointer to the root command.
     */
    command_tree(std::shared_ptr<command> root);

    /**
     * @brief Complete a command based on the provided partial input.
     *
     * Modifies the provided input string to complete the command based on the
     * available options in the command tree.
     *
     * @param input Partial input string to be completed.
     */
    void complete_command(std::string& input);

    /**
     * @brief Get a vector of complete options based on the provided partial input.
     *
     * Returns a vector of complete options that match the provided partial input.
     *
     * @param partial_input Partial input string.
     * @return Vector of complete options.
     */
    std::vector<std::string> get_complete_options(const std::string& partial_input);

    /**
     * @brief Execute a command based on the provided input.
     *
     * Executes the command specified by the input string and returns the result.
     *
     * @param input Input string representing the command.
     * @return Result of executing the command.
     */
    command_result execute_command(const std::string& input);

private:
    /**
     * @brief Complete a composite command based on the provided partial input.
     *
     * Modifies the provided input string to complete the composite command based
     * on the available options in the command tree.
     *
     * @param composite_command Shared pointer to the composite command.
     * @param input Partial input string to be completed.
     * @param current_path Current path in the command tree.
     */
    void complete_composite_command(const std::shared_ptr<composite_command> composite_command,
        std::string& input, const std::string& current_path);

    /**
     * @brief Complete the path in the command tree based on the provided partial input.
     *
     * Modifies the provided input string to complete the path based on the available
     * options in the command tree.
     *
     * @param input Partial input string to be completed.
     * @param current_path Current path in the command tree.
     */
    void complete_path(std::string& input, const std::string& current_path);

    /**
     * @brief Get a vector of options for a composite command based on the provided partial input.
     *
     * Returns a vector of options for a composite command that match the provided partial input.
     *
     * @param composite_command Shared pointer to the composite command.
     * @param partial_input Partial input string.
     * @return Vector of options for the composite command.
     */
    std::vector<std::string> get_composite_command_options(
        const std::shared_ptr<composite_command> composite_command, const std::string& partial_input);

    /**
     * @brief Get a vector of options for the path based on the provided partial input.
     *
     * Returns a vector of options for the path that match the provided partial input.
     *
     * @param partial_input Partial input string.
     * @return Vector of options for the path.
     */
    std::vector<std::string> get_path_options(const std::string& partial_input);

    /**
     * @brief Parse the tree path from the provided input string.
     *
     * Parses the tree path from the input string and returns a tuple containing the
     * shared pointer to the command and the remaining path.
     *
     * @param input Input string representing the command and path.
     * @return Tuple containing the shared pointer to the command and the remaining path.
     */
    std::tuple<std::shared_ptr<command>, std::string> get_parsed_tree_path(const std::string& input);

    /**
     * @brief Find the longest common prefix among a set of strings.
     *
     * Finds the longest common prefix among a set of strings.
     *
     * @param options Set of strings to find the common prefix.
     * @return The longest common prefix.
     */
    std::string longest_common_prefix(const std::set<std::string>& options);

    std::shared_ptr<command> _root;
};

#endif
