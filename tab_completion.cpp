//#ifndef TAB_COMPLETION_H_
//#define TAB_COMPLETION_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
// main crux is to immplement file system scan 

// TODO all commands should be SORTED alphabetically -> it will be easier, but it is not library usage
// TODO lets have map of commands -> this is nice solution

// i will pres tab and have also current word
// well these can be static functions
class tab_completion {
public:
	/*
	tab_completion(){
		// commands, and bool has file
		// int is for flags, maybe bool is enough
		// 0 -> argument is path (you have to recognize somehow if it is )
		std::map<std::string, int> commands
	
	} */
	tab_completion();

	tab_completion(const std::map<std::string, int>& commands);

	void add_command(std::string name, int flags);

	// returns longest common prefix
	std::string get_command_match(const std::string& prefix, const std::vector<std::string>& commands);

	std::string get_path_match(const std::string& prefix);	
private:
	std::string longest_common_prefix(std::vector<std::string>& commands);

	std::map<std::string, int> _commands;
};

tab_completion::tab_completion() : _commands() {}

tab_completion::tab_completion(const std::map<std::string, int>& commands) : _commands(commands) {}
//#endif

// tohle nefunguje
std::string tab_completion::longest_common_prefix(const std::map<std::string, int>& commands){
	if(commands.empty()){
		return "";
	}

	std::string first = *(commands.begin());
	std::string last = *(commands.end() - 1);
	std::string result;

	for(int i=0; i < std::min(first.length(), second.length()); i++){
		if(first[i] != last[i]){
			break;
		}

		result += first[i];
	}

	return result;
}

std::string tab_completion::get_command_match(const std::string& prefix){
	std::map<std::string, int> commands_subset;
	
	for(const auto& pair : commands){
		if(pair.first.rfind(prefix)){
			commands_subset[pair.first] = pair.second;
		}
	}

	return longest_common_prefix(commands_subset);
}


int main(){
	//std::cout << tab_completion::get_command_match() << std::endl;
	
	tab_completion t({{"aaa", 1}, {"abc", 2}, {"abb", 3}});
	std::cout << t.get_command_match
}


