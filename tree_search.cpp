#include <iostream>
#include <string>
#include <algorithm>
#include <filesystem>
namespace fs = std::filesystem;

bool starts_with(const std::string& str, const std::string& prefix){
	return std::equal(prefix.begin(), prefix.end(), str.begin());
}

#include <set>

class command{
public:
	command(const std::string& name) : name(name) {}
	std::string name;


	bool operator<(const command& other) const{
		return name < other.name;
	}
};



int main() {
	fs::path directory_path = ".";  // cant be empty, then exception is raised 
	std::string prefix = "";

	
	
	for(const auto& entry : fs::directory_iterator(directory_path)){
		if(fs::is_directory(entry) ){ //&& entry[0] != '.'){
			// std::cout << entry.path() << std::endl;
			std::cout << entry.path().filename() << std::endl;
		} else if(fs::is_regular_file(entry)){ // && entry[0] != '.'){
			// std::cout << entry<< std::endl;
			std::cout << entry.path().filename() << std::endl;
		}
	}

	std::set<command> s;

	/*
	for(int i=65; i < 80; ++i){
		std::cout << (char)i + "a";
		s.insert(command((char)i));
	} */

	s.insert(command("aa"));
	s.insert(command("ab"));
	s.insert(command("ac"));
	s.insert(command("ad"));

	auto itr = s.begin();
	auto result = s.find(command("ab")) != s.end();
	std::cout << result << std::endl;

	for(auto itr : s){
		std::cout << itr.name << std::endl;
	}

	return 0;
}

