#include <iostream>
#include <string>
#include <vector>
#include <set>


class history{
public:
	history();
	// TODO remember commands history and fetch it at start of program
	void add(const std::string& command);

	void move_next();

	void move_back();

	std::string get_current();

	std::set<std::string> search_for(const std::string& pattern);
private:
	std::vector<std::string> _previous_commands;
	size_t _current_index;
};

history::history() : _previous_commands(), _current_index(-1) {}

void history::add(const std::string& command){
	_previous_commands.push_back(command);
	_current_index = _previous_commands.size();
}

void history::move_next(){
	if(_current_index < _previous_commands.size()){
		_current_index++;
	}
}

void history::move_back(){
	if(_current_index > 0){
		_current_index--;
	}
}

std::string history::get_current(){
	if(_current_index < 0 || _current_index >= _previous_commands.size()){
		return "";
	}

	return _previous_commands[_current_index]; 
}

int main(){
	history h;
	
	h.add("ahoj");
	h.add("jak");
	h.add("se");
	h.add("mas");

	for(int i=0; i < 10; ++i){
		std::cout << h.get_current() << std::endl;
		h.move_back();
	}

	std::cout << std::cin.get() << std::endl;
}
