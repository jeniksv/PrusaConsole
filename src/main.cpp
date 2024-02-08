#include <dbus-cxx.h>

#include <memory>
#include <optional>
#include <string>

#include "cli.hpp"

int main(int argc, char** argv)
{
    /*
    std::shared_ptr<DBus::Dispatcher> dispatcher =
    DBus::StandaloneDispatcher::create(); std::shared_ptr<DBus::Connection>
    connection = dispatcher->create_connection( DBus::BusType::SYSTEM );
    std::shared_ptr<DBus::ObjectProxy> object =
    connection->create_object_proxy("cz.prusa3d.sl1.printer0",
    "/cz/prusa3d/sl1/printer0"); DBus::MethodProxy<void()>& add_proxy =
    *(object->create_method<void()>("cz.prusa3d.sl1.printer0","tilt_home"));
    add_proxy();
    */
    // try{
    cli _cli;
    _cli.mainloop();
    //} catch(...) {}
}
