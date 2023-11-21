#include "command.hpp"
#include "tab_completion.hpp"
#include "history.hpp"


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
	
	//std::cout << tab_completion::get_command_match() << std::endl;

	tab_completion t({"aaaaa", "aabc", "aabb"});
	std::cout << t.get_command_match("a") << std::endl;

	// auto r = t.get_command_matches("aab");

	// for(auto& i : r) std::cout << i << std::endl;
	std::cout << t.get_path_match("/home/jenda/Dow") << std::endl;
	std::cout << t.get_path_match("s") << std::endl;

	/*
	 * TODO should be only code in main
	 * console_UI{
	 * public:
	 * 	mainloop(){
	 *		while(true){
	 *			std::string line = _reader.readline();
	 *			command = _parser.parseline(line);
	 *			command.execute(); 
	 *		}
	 * 	}
	 * private:
	 * 	console_reader _reader;
	 * 	command_parser _parser;
	 * }
	 * std::unique_ptr<user_interface> ui = new console_UI();
	 * ui->mainloop();
	 */
} 
