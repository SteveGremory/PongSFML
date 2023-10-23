cmake_minimum_required(VERSION 3.22)
project(PongSFML)

# Set C++ options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Clang tidy setup
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=*,-llvmlibc-*,-google-*,-fuchsia-*,-android-*,-altera-*,-abseil-*,-boost-*,-objc-*,-openmp-*,-zircon-*,-misc-include-cleaner")

# Add SFML as a dependency
add_subdirectory(deps/SFML)

# Get all the C++ files
# in the sources recursively
file(GLOB_RECURSE PONG_SOURCES
    source/*.cpp
)

# Create the project
add_executable(pong ${PONG_SOURCES})
target_include_directories(pong PRIVATE 
    source/
)

# Link SFML
target_link_libraries(pong PRIVATE
    sfml-graphics
)

# Enable address sanitizer and Extra warnings
target_compile_options(pong PRIVATE
    -Wall -Wextra
    -fsanitize=address
)
target_link_options(pong PRIVATE -fsanitize=address)

# Use clang tidy to get even more warnings when in debug mode
# set_target_properties(pong PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")