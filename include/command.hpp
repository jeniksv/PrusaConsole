#ifndef COMMAND_H_
#define COMMAND_H_

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stack>


enum class command_result{
	OK,
	INVALID_ARGUMENTS,
	UNKNOWN_COMMAND,
	NOT_IMPLEMENTED,
	EXIT,
};


class command{
public:
	command(const std::string&, bool);

	virtual ~command() = default;

	const std::string& get_name() const;

	bool is_leaf() const;

	bool starts_with(const std::string&) const;

	virtual command_result execute(std::stringstream&) = 0;
protected:
	std::string _name;
	bool _leaf;
};


class concrete_command_base : public command{
public:
	concrete_command_base(const std::string&);

	virtual ~concrete_command_base() = default;

	virtual command_result execute(std::stringstream&) = 0;

	virtual std::string help();
protected:
	void init_args_vector(std::stringstream&);

	std::vector<std::string> _args_vector;
};


class composite_command : public command{
public:
	composite_command();
	
	composite_command(std::string);

	void add_command(std::shared_ptr<command>);

	const std::vector<std::shared_ptr<command>>& get_children() const;

	command_result execute(std::stringstream&) override;
private:
	std::vector<std::shared_ptr<command>> _children;
};


struct command_comparator{
	bool operator()(const command&, const command&) const;
};

#endif
