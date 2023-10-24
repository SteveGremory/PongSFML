cmake_minimum_required(VERSION 3.22)
project(PongSFML)

# Set C++ options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
    sfml-audio
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
message("-- Using libasan")
# Enable address sanitizer and Extra warnings
target_compile_options(pong PRIVATE
    -Wall -Wextra
    -fsanitize=address
    -fsanitize=leak
)
target_link_options(pong PRIVATE -fsanitize=address)
endif()
