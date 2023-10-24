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

# Copy the assets to the build folder
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

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

# Windows fiasco
if (WIN32)
  add_custom_command(TARGET pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/deps/SFML/extlibs/bin/x64/openal32.dll $<TARGET_FILE_DIR:pong>
  )
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT pong)
endif()


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
