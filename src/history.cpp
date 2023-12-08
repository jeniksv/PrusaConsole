#include "history.hpp"

history::history() : _current_commands(), _current_index(), _history_file_name(".history_history") {
	fetch_history();
	reset();
}

history::history(const std::string& file_name) : _current_commands(), _current_index(), _history_file_name(file_name) {
	fetch_history();
	reset();
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
	if(std::all_of(command.begin(), command.end(), [](char c){ return std::isspace(c); })){
		return;
	}
	
	if(!_current_commands.empty() && command == _current_commands.back()){
		return;
	}

	
	_current_commands.push_back(command);
	_current_index = _current_commands.size() - 1;
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

void history::reset() {
	_current_index = _current_commands.size() - 1;
}
