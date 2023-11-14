#include "command.hpp"
#include "tab_completion.hpp"
#include "history.hpp"


int main(){
	history h;
  	//std::cout << tab_completion::get_command_match() << std::endl;

        tab_completion t({"aaaaa", "aabc", "aabb"});
        std::cout << t.get_command_match("a") << std::endl;

        // auto r = t.get_command_matches("aab");

        // for(auto& i : r) std::cout << i << std::endl;
        std::cout << t.get_path_match("/home/jenda/Dow") << std::endl;
        std::cout << t.get_path_match("tab") << std::endl;
} 
}
