#include "console_reader.hpp"
#include <map>
#include <memory>

unix_console_IO::unix_console_IO() : _history(), _tab_completion() {
	FILE *f = fopen("/dev/tty", "rw");
	SCREEN *s = newterm(nullptr, f, f);
	set_term(s);

	//enables keypad mode
	keypad(stdscr, TRUE);
}

unix_console_IO::~unix_console_IO() override{
	endwin();
	fclose();
}

void unix_console_IO::write(const std::string& str) override{
	printw(str);
}

// TODO maybe just use shared_ptr<>
std::string unix_console_IO::read_line() override{
	std::map<int, std::unique_ptr<key_action_base>> key_actions = {
		{1 , std::make_unique<key_action_base>(arrow_key_action(history()))},

	};

	std::string current_line;
	
	while(true){
		int key = getch();
		
		if(key_actions.contains(key)){
			current_line = key_actions[key]->modify_current(current_line);
		}

		if(key == ENTER_KEY){
			return current_line;
		}
	}
}


