#ifndef CONSOLE_READER_H_
#define CONSOLE_READER_H_

#include <dbus-cxx.h>
#include <string>

#include "cpp-terminal/cursor.hpp"
#include "cpp-terminal/exception.hpp"
#include "cpp-terminal/input.hpp"
#include "cpp-terminal/iostream.hpp"
#include "cpp-terminal/key.hpp"
#include "cpp-terminal/options.hpp"
#include "cpp-terminal/screen.hpp"
#include "cpp-terminal/terminal.hpp"
#include "cpp-terminal/tty.hpp"
#include "cpp-terminal/version.hpp"

#include "history.hpp"
#include "key_actions.hpp"
#include "printer.hpp"

/**
 * @brief Command Line Interface (CLI) Class
 *
 * The `cli` class represents a simple command-line interface with a main loop.
 * It provides functionality for handling user input, managing history, and printing
 * output to the console.
 */
class cli {
public:
    /**
     * @brief Constructor for the CLI class.
     *
     * Initializes the CLI object with default settings.
     */
    cli();

    /**
     * @brief Main loop for the CLI.
     *
     * Enters the main loop of the CLI, where it continuously waits for user input,
     * processes the input, and performs the corresponding actions.
     */
    void mainloop();

private:
    /**
     * @brief Reset the internal state of the CLI.
     *
     * Resets the internal state of the CLI, including any temporary variables or
     * user-specific settings.
     */
    void reset_state();

    /**
     * @brief Flag indicating whether the CLI is currently running.
     */
    bool _running;

    /**
     * @brief The current line of user input being processed.
     */
    std::string _current_line;

    /**
     * @brief History object to manage command history.
     */
    history _history;

    /**
     * @brief Printer object responsible for printing output to the console.
     */
    printer _printer;

    /**
     * @brief Key action factory to generate actions based on user input.
     */
    key_action_factory _key_action_factory;
};

#endif
