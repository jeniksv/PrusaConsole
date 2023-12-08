#ifndef HISTORY_H_
#define HISTORY_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

// specific behaviour:
// 	-> if command contains only white spaces, it is not added to history
// 	-> if command, which should be added to history is same as last command in history, it is not added to history

class history {
public:
        history();

        history(const std::string&);

        ~history();

        void add(const std::string&);

        void move_next();

        void move_back();

        std::string get_current();

	void reset();

        //
        // iterates only through commands which has common prefix with string pattern
        //
        void enable_pattern_matching(const std::string&);

        void disable_pattern_matching();
private:
        void fetch_history();

        // std::vector<std::string> _all_commands; // last command is last element in _prev_commands
        std::vector<std::string> _current_commands;
        size_t _current_index;
        const std::string _history_file_name;
};

#endif
