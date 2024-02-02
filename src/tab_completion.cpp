#include "tab_completion.hpp"

#include <filesystem>
#include <iostream>
// TODO use stringstream instead of std::string
/*
tab_completion::tab_completion() : _commands() {}

tab_completion::tab_completion(const std::set<std::string>& commands) : _commands() {
	for(const std::string& s : commands){
		_commands.insert(command(s));
	}
}

// TODO ctor for every iterabel collection 
tab_completion::tab_completion(const std::set<command, command_comparator>& commands) : _commands(commands) {}

void tab_completion::add_command(const command& command){
	_commands.insert(command);
}

void tab_completion::remove_command(const command& command){
	_commands.erase(command);
}

std::vector<std::string> tab_completion::get_command_matches(const std::string& prefix){
	return get_commands_subset(prefix);
}


std::vector<std::string> tab_completion::get_commands_subset(const std::string& prefix){
        std::vector<std::string> result;

        for(const command& c : _commands){
                if(c.starts_with(prefix)){
                        result.push_back(c.get_name());
                }
        }

        return result;
}

// TODO use std::set instead of vector 
// not so obvious that i filter this vector from set
std::string tab_completion::longest_common_prefix(std::vector<std::string>& commands){
	if(commands.empty()){
		return "";
	}
	
	if(!std::is_sorted(commands.begin(), commands.end())){
		std::sort(commands.begin(), commands.end());
	}

	std::string first = *(commands.begin());
	std::string last = *(commands.end() - 1);
	std::string result;

	for(unsigned int i=0; i < std::min(first.length(), last.length()); i++){
		if(first[i] != last[i]){
			break;
		}

		result += first[i];
	}

	return result;
}


std::string tab_completion::get_command_match(const std::string& prefix){
	std::vector<std::string> temp = get_commands_subset(prefix);
	return longest_common_prefix(temp);
}


std::string tab_completion::get_path_match(const std::string& prefix){
	std::string current_directory(std::filesystem::path(prefix).parent_path().string());
	std::string current_prefix(std::filesystem::path(prefix).filename().string());

	current_directory = current_directory.empty() ? "." : current_directory;
	
	std::vector<std::string> matches;

	for(const auto& entry : std::filesystem::directory_iterator(current_directory)){
		std::string filename = entry.path().filename().string();
		
		if(!std::equal(current_prefix.begin(), current_prefix.end(), filename.begin())){
			continue;		
		}

		if(std::filesystem::is_directory(entry) || std::filesystem::is_regular_file(entry)){
			matches.push_back(filename);
		}
	}

	// for(auto i : matches){std::cout << i << std::endl; }

	current_directory = current_directory == "." ? "" : current_directory.append("/");
	return current_directory.append(longest_common_prefix(matches));
}*/
