#include "tab_completion.hpp"

#include <iostream>
// main crux is to immplement file system scan 
// current word for tab completion is [A-z0-9] from last white character

/*
class tab_completion {
public:
        void add_command(const std::string& name);

        void remove_command(const std::string& name);

        std::string get_command_match(const std::string& prefix);

        std::string get_path_match(const std::string& prefix);
private:
	std::vector<std::string> get_commands_subset(const std::string& prefix);

        std::string longest_common_prefix(std::vector<std::string>& commands);

        std::set<std::string> _commands;
};
*/


tab_completion::tab_completion(const std::set<std::string>& commands) : _commands(commands) {}

std::vector<std::string> tab_completion::get_command_matches(const std::string& prefix){
	return get_commands_subset(prefix);
}

std::vector<std::string> tab_completion::get_commands_subset(const std::string& prefix){
        std::vector<std::string> result;

        for(const std::string& s : _commands){
                if(s.rfind(prefix, 0) == 0){
                        result.push_back(s);
                }
        }

        return result;
}


std::string tab_completion::longest_common_prefix(const std::vector<std::string>& commands){
	if(commands.empty()){
		return "";
	}

	std::string first = *(commands.begin());
	std::string last = *(commands.end() - 1);
	std::string result;

	for(int i=0; i < std::min(first.length(), last.length()); i++){
		if(first[i] != last[i]){
			break;
		}

		result += first[i];
	}

	return result;
}

std::string tab_completion::get_command_match(const std::string& prefix){
	return longest_common_prefix(get_commands_subset(prefix));
}


int main(){
	//std::cout << tab_completion::get_command_match() << std::endl;
	
	tab_completion t({"aaaaa", "aabc", "aabb"});
	std::cout << t.get_command_match("a") << std::endl;

	auto r = t.get_command_matches("aab");

	for(auto& i : r) std::cout << i << std::endl;
}


