#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <algorithm>

// teoreticky tohle muze byt predek jenom, od kteryho budou dedit konkretni commandy
// TODO mozna pouzit special vlakno pro praci s dbusem?
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

// TODO musi to byt navrzeny tak, aby se pridala jedna trida a pridalo se to potom do nejake factory, to pak uplne staci
// takze command factory, kde se bude primo parsovat ten string?

// command_base
class command{
public:
	command(const std::string&);

	std::string get_name() const;

	void execute(); // TODO virtual? and then also virtual destructor

	bool starts_with(const std::string&) const;
private:
	std::string _name;
};

// TODO command factory

struct command_comparator{
	bool operator()(const command&, const command&) const;
};

/*
class print_start_command(){
public:
	
}
*/

#endif
