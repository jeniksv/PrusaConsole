#ifndef CONSOLE_READER_H_
#define CONSOLE_READER_H_

#include <string>
#include <memory>
#include <ncurses.h>

#include "key_actions.hpp"


class console_IO_base{
public:
	virtual ~console_IO_base();

	virtual void write(std::string str) = 0;
	
	virtual std::string read_line() = 0;
};


class unix_console_IO : public console_reader_base{
public:
	unix_console_IO();

	~unix_console_IO() override;

	void write(const std::string& str) override;

	std::string read_line() override;
private:
	// will not be private, i should pass it to specific action commands
	std::shared_ptr<history> _history_ptr;
	std::shared_ptr<tab_completion> _tab_completion_ptr;
};

/*
 * while(true){
 * 	key k = get_key();
 *	
 *	TODO handle with templates
 *	map with lambda functions
 *
 *	map<key_event, unique_ptr<command_base>> actions;
 *
 *	if(k.type == key_event::ENTER){
 *		return current;
 *	} else if(k.type == key_event::TAB) {
 *		if(tab_double_tap){
 *			for(const std::string& s : t.get_matches(current)){
 *				write_line(s);
 *			}
 *		} else {
 *			current = t.get_match()
 *		}
 *		current = double_tap ? get_matches
 *	} else if() ...
 *		
 *
 */

#endif

