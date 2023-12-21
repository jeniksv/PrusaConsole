#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <algorithm>

// TODO tady se da v podstate pouzit ten starej stringovej protokol baseboard.do
enum class dbus_action {
	START_PRINT, // path to project
	STOP_PRINT,

	// advanced commands
	SHOW_LAYER_INFO, // -> should display exposure0state, layer number
	SHOW_LAYER_PNG, // path to project ..., tohle by se dalo vypisovat u layer_info
	
	// motor control
	SET_TILT_POSITION,
	SET_TOWER_POSITION,
	SET_PUMP_POSITION,
	SET_LED_DURATION,

	STOP_TILT_MOVEMENT,
	STOP_TOWER_MOVEMENT,
	STOP_PUMP_MOVEMENT,

	GET_TILT_POSITION, //maybe not only position, but all properties, homing status ...
	GET_TOWER_POSITION,
	GET_PUMP_POSITION, // optional, how long do you want to read position

	GET_LOADCELL_DATA, // optional, how long do you want to read them
	GET_RESIN_STATE, // used, in canister ...

	GET_REMAING_TIME // in seconds
};

/*
enum class command_state {
	OK,
	INVALID_ARGUMENT,
	UNKNOWN_COMMAND,
	
};
*/

// app will start with ./prusa_console --sl2 (--sl1, --sl1s, mk1, )



// TODO rename to command_base
class command{
public:	
	command(const std::string&);

	virtual ~command();

	std::string get_name() const;

	bool starts_with(const std::string&) const;

	virtual void execute(const std::vector<std::string>&); // = 0; TODO make pure virtual, also vector can be const

	//default, prints help for command -> kdyz se zavola help command, projede to vsechny commandy tiskarny a na nich zavola ->help();
	virtual void help();
private:
	std::string _name;
};


struct command_comparator{
	bool operator()(const command&, const command&) const;
};


class exit : public command{
public:
	void execute(const std::vector<std::string>&) override;
};

class start_print : public command{
public:
	
};

class stop_print : public command{
public:
};

#endif
