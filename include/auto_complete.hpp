#ifndef AUTOCOMPLETE_H_
#define AUTOCOMPLETE_H_

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <sstream>


class trie_node{
public:
	std::map<char, std::unique_ptr<trie_node>> children;

	bool is_word_end();

	void set_word_end();
private:
	bool _word_end;
};

class auto_complete{
public:
	void add_command(const std::string&);

	//fluent API with_subcommand();
	//void add_subcommand()

private:

};
/*
 * dostanes strukturu -> command_structure
 * 	moznosti
 * 	command("tilt").with_subcommand(command("set_position", action)).with_subcommand(command("get_position", action))

#define
