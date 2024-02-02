#ifndef CONSOLE_READER_H_
#define CONSOLE_READER_H_

#include <string>

#include "history.hpp"
#include "key_actions.hpp"
#include "printer.hpp"
#include "parser.hpp"

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


class cli{
public:
	cli();

	void mainloop();
private:
	void reset_state();

	bool _running;
	std::string _current_line;

	history _history;
	printer _printer;
	key_action_factory _key_action_factory;
};

#endif
