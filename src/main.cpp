#include "cli.hpp"

int main(int argc, char** argv)
{
    try {
        cli _cli;
        _cli.mainloop();
    } catch (...) {
        std::cerr << "DBUS Error" << std::endl;
    }
}
