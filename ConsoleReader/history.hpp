#ifndef HISTORY_H_
#define HISTORY_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class history {
public:
        history();

        history(const std::string& file_name);

        ~history();

        void add(const std::string& command);

        void move_next();

        void move_back();

        std::string get_current();

        //
        // iterates only through commands which has common prefix with string pattern
        //
        void enable_pattern_matching(const std::string& pattern);

        void disable_pattern_matching();
private:
        void fetch_history();

        // std::vector<std::string> _all_commands; // last command is last element in _prev_commands
        std::vector<std::string> _current_commands;
        size_t _current_index;
        const std::string _history_file_name;
};

#endif
