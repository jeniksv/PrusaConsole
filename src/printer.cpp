#include "printer.hpp"
#include "cpp-terminal/iostream.hpp"

/*
printer::printer() : _command_tree(), _type("sl2") {
	build_sl2();
	__commands = command_tree(_command_tree);

}
*/
/*
printer:
	// what about _command_tree = command_tree_builder.build("type");

	if(sl1):
		command_tree_builder = 
	if(sl2):
		command_tree_builder = 
*/

printer::printer(){
	build_sl2();
}

std::string printer::get_type(){
	return _type;
}

command_tree& printer::get_command_tree(){
	return _command_tree;
}

command_result printer::dbus_request(const std::string& request){
	if(request.empty()){
		return command_result::OK;
	}

	return _command_tree.execute_command(request);
}

void printer::build_sl2(){
	_command_tree = command_tree_builder()
        .add_core_commands()
        .add_composite_command("tilt")
            .add_composite_command("position")
                 .add_concrete_command(std::make_shared<default_command>("get"))
                 .add_concrete_command(std::make_shared<default_command>("set"))
            .end_composite_command()
            .add_concrete_command(std::make_shared<default_command>("home"))
        .end_composite_command()

        .add_composite_command("tower")
            .add_composite_command("position")
                 .add_concrete_command(std::make_shared<default_command>("get"))
                 .add_concrete_command(std::make_shared<default_command>("set"))
            .end_composite_command()
            .add_concrete_command(std::make_shared<default_command>("home"))
        .end_composite_command()

        .add_composite_command("pump")
            .add_composite_command("position")
                 .add_concrete_command(std::make_shared<default_command>("get"))
                 .add_concrete_command(std::make_shared<default_command>("set"))
            .end_composite_command()
            .add_concrete_command(std::make_shared<default_command>("home"))
        .end_composite_command()

        .add_composite_command("uv_led")
            .add_concrete_command(std::make_shared<default_command>("duration"))
            .add_concrete_command(std::make_shared<default_command>("temperature"))
        .end_composite_command()
        .add_composite_command("print")
            .add_concrete_command(std::make_shared<default_command>("start"))
            .add_concrete_command(std::make_shared<default_command>("stop"))
        .end_composite_command()
        .build();
}
