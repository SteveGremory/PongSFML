# Pong

A classic Atari pong replica written in C++ using the SFML graphics/audio libraries.

# Compilation

To build the project, you _must_ clone it recursively, like so:
`git clone https://github.com/SteveGremory/PongSFML --recursive`

Afterwards, change the directory into the project root and run this CMake command to generate build files:
`cmake . -Bbuild`

this will create a build folder wherein the platform specific build files lay. On UNIX-Like OSes, `make` or `ninja` can be used and a Visual Studio solution will be generated on Windows by default.

# Running

Currently it's only supported to run the executable from _within_ the build folder so as to provide the right paths for the assets. So after changing the current directly to the build folder, simply execute it from within, like so:

`cd build; ./pong`
