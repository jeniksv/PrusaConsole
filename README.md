# PrusaConsole
Command line interface for latest Prusa3D printers.

### Getting started

**Note:** The current codebase is optimized for execution on Ubuntu 22.04. It is important to mention that running the code on Windows is not supported due to the lack of D-BUS interface support in the Windows environment.

Before the first run, install all required dependencies with:

```
./scripts/dependency_setup.sh
```

To build the project, you can use either CMakeLists or the convenient `scripts/project.sh` script:

```
./scripts/project.sh --build
```

Alternatively:

```
git submodule update --init --recursive
mkdir build && cd build && cmake .. && make -j12
```

For project cleanup, use:
```
./scripts/project.sh --clean
```

Run tests with:
```
./scripts/project.sh --test
```

### Usage

The usage is as follows:

```
> help
> tilt position set 1000
> tilt home
> print start /home/jeniksv/project.sl1s
> exposure current_layer
```

### Testing

For testing and development without a physical printer, set up a virtual printer. If you're using an SLx printer type, you can set it up with:

```
./scripts/run_virtual.sh
```

### PrusaConsole2

Current version is designed to run directly on the printer. The upcoming version aims to split the application into two parts: a D-BUS server and a multi-platform command-line interface client.

### Caveats

While external libraries like dbus-cxx (written in C++) and cpp-terminal are effective, there's room for improvement. Considering that the master system is already written in Python, the pydbus package emerges as a more streamlined alternative. It is not only written in Python but also extensively tested and well-documented, making it a natural fit for seamless integration. This shift to pydbus aligns the server-side language with the overall system, enhancing compatibility and maintainability.s

### Contributing

PrusaConsole is open to contributions for new printers or printer components. Feel free to submit a merge request with your code changes, ensuring that tests remain intact.
