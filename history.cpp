#include "history.hpp"

history::history() : _current_commands(), _current_index(-1), _history_file_name(".history_history") {
	fetch_history();
}

history::history(const std::string& file_name) : _current_commands(), _current_index(-1), _history_file_name(file_name) {
	fetch_history();
}

history::~history() {
	int last_index = std::max(0, static_cast<int>(_current_commands.size()) - 100);
	std::ofstream output_file(_history_file_name);

	for(size_t i = last_index; i < _current_commands.size(); i++){
		output_file << _current_commands[i] << std::endl;
	}

	output_file.close();
}

void history::fetch_history() {
        std::ifstream input_file(_history_file_name);

        if(!input_file.is_open()){
                return;
        }

        std::string line;

        while(std::getline(input_file, line)){
                _current_commands.push_back(line);
        }

        input_file.close();
}

void history::add(const std::string& command) {
	_current_commands.push_back(command);
	_current_index = _current_commands.size();
}

void history::move_next() {
	if(_current_index < _current_commands.size()){
		_current_index++;
	}
}

void history::move_back() {
	if(_current_index > 0){
		_current_index--;
	}
}

std::string history::get_current() {
	if(_current_index < 0 || _current_index >= _current_commands.size()){
		return "";
	}

	return _current_commands[_current_index]; 
}


int main(){
	history h(".console_reader_history");
	
	h.add("ahoj");
	h.add("jak");
	h.add("se");
	h.add("mas");

	for(int i=0; i < 10; ++i){
		std::cout << h.get_current() << std::endl;
		h.move_back();
	}
}
