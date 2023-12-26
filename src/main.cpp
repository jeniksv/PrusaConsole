#include <vector>
#include <sstream>

#include "command.hpp"
#include "tab_completion.hpp"
#include "history.hpp"
#include "console_reader.hpp"
#include "printer.hpp"


// TODO jediny pruchod takze to nebude static
// ted je to docela hnusny ale je to vsem jedno a funguje to
// TODO hlavne pouzij stringstream
// argumenty by to chtelo vracet jako optional, tim se pak muzu kontrolovat ciste nullptr
class parser{
public:
	static std::string strip_line(const std::string& line, const std::string &chars = " \t\n\r"){
		size_t begin = line.find_first_not_of(chars);
		size_t end = line.find_last_not_of(chars);
	
		if(begin == std::string::npos || end == std::string::npos){
			return "";
		}

		return line.substr(begin, end - begin + 1);
	}

	static std::vector<std::string> split_line(const std::string& line, const std::string &chars = " \t\n\r"){
		std::vector<std::string> result;
		std::stringstream ss(line);
		std::string token;

		while (std::getline(ss, token, ' ')) {
			if (!token.empty()) {
				result.push_back(token);
			}
		}

		return result;
	}

	static std::string get_command_name(const std::string& line, const std::string &chars = " \t\n\r"){
		std::vector<std::string> line_splitted  = parser::split_line(line);
		return line_splitted.size() > 0 ? line_splitted[0] : "";
	}

	static std::vector<std::string> get_args(const std::string& line, const std::string &chars = " \t\n\r"){
		std::vector<std::string> line_splitted  = parser::split_line(line);
		//return line_splitted.size() > 1 ? std::vector<std::string>(line.begin() + 1, line.end()) : std::vector<std::string>();
		if (line_splitted.size() > 1) {
			std::vector<std::string> args(line_splitted.begin() + 1, line_splitted.end());
			return args;
		}

		return std::vector<std::string>();
	
	}
};

int main(int argc, char** argv){
	/*
	if(argc != 2){
		Term::cout << "argument error" << std::endl;
		exit(0);
	}
	*/
	
	printer p; //(argv[1]);
	//std::cout << p.valid_command("ahoj") << std::endl;

	console_reader reader;
	
	while(true){
		std::string line = reader.read_line();
		
		line = parser::strip_line(line);

		std::string c = parser::get_command_name(line);
		std::vector<std::string> args = parser::get_args(line);
		//auto temp = parser::get_command_name(line);
		//Term::cout << "commandx" << temp << "x" << std::endl;
		//temp = parser::get_args(line);
		//Term::cout << "argsx" << temp << "x" << std::endl;
		//for(auto&& s : parser::get_args(line)) Term::cout << s << std::endl;
		if(line == "exit"){ break; }
		
		if(p.valid_command(c)){
			p.get_action(c)->execute(args);
		} else {
			Term::cout << "Invalid command" << std::endl;
		}
		// command.execute()
	}
}
