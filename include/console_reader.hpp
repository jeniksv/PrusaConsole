#ifndef CONSOLE_READER_H_
#define CONSOLE_READER_H_

#include <string>

#include "tab_completion.hpp"
#include "history.hpp"
#include "key_actions.hpp"

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

class console_reader{
public:
	console_reader();

	// console_reader(history&, tab_completion&); 
	void clear_line(const std::string&);	

	std::string read_line();
private:
	void write_line(const std::string&);
	// TODO necessary? -> can just create it in ctor
	history _history;
	tab_completion _tab;
	key_action_factory _key_action_factory;
};

#endif
