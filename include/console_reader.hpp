#ifndef CONSOLE_READER_H_
#define CONSOLE_READER_H_

#include <string>

enum class key_event {
	ENTER,
	NO_ACTION_KEY,
	BACKSPACE,
	TAB,
	ARROW_LEFT,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	// TODO ctrl, alt, shift actions
};

class key{
public:
	key(key_event e);
	key(key_event e, int v);
	
	key_event type;
	int value;
};

// std::unique_ptr<command_base>

class console_IO_base{
public:
	virtual ~console_IO_base();

	virtual void write_char(char k) = 0;
	virtual void write_line(std::string line) = 0;
	
	virtual char read() = 0;
	// virtual char read(int count) = 0;
	virtual key read_key() = 0;
	virtual std::string read_line() = 0;
};

/*
class unix_console_IO : public console_reader_base{
public:
	key read_key();
	std::string read_line() override;
private:
	key_event get_key();

	write_char
	history _history;
	tab_completion _tab_completion;
};
*/
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

