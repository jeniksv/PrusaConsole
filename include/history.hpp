#ifndef HISTORY_H_
#define HISTORY_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Class representing command history.
 *
 * The `history` class manages a history of commands entered by the user
 * and provides navigation and manipulation functionalities.
 */
class history {
public:
    /**
     * @brief Default constructor for the history class.
     *
     * Initializes an empty command history.
     */
    history();

    /**
     * @brief Constructor for the history class with a specified history file.
     *
     * Initializes the command history and loads commands from the specified file.
     *
     * @param history_file_name The name of the history file.
     */
    history(const std::string& history_file_name);

    /**
     * @brief Destructor for the history class.
     *
     * Cleans up resources and saves the command history to the history file.
     */
    ~history();

    /**
     * @brief Add a command to the history.
     *
     * Adds a command to the history, excluding commands with only white spaces
     * and duplicates of the last command in the history.
     *
     * @param command The command to be added to the history.
     */
    void add(const std::string& command);

    /**
     * @brief Move to the next command in the history.
     */
    void move_next();

    /**
     * @brief Move to the previous command in the history.
     */
    void move_back();

    /**
     * @brief Get the current command in the history.
     *
     * @return The current command in the history.
     */
    std::string get_current();

    /**
     * @brief Get the next command in the history.
     *
     * @return The next command in the history.
     */
    std::string get_next();

    /**
     * @brief Get the previous command in the history.
     *
     * @return The previous command in the history.
     */
    std::string get_previous();

    /**
     * @brief Reset the history navigation to the current command.
     */
    void reset();

    /**
     * @brief Enable pattern matching for history commands.
     *
     * @param pattern The pattern to be used for matching commands.
     */
    void enable_pattern_matching(const std::string& pattern);

    /**
     * @brief Disable pattern matching for history commands.
     */
    void disable_pattern_matching();

private:
    /**
     * @brief Fetch command history from the history file.
     */
    void fetch_history();

    std::vector<std::string> _current_commands;
    size_t _current_index;
    const std::string _history_file_name;
};

#endif
