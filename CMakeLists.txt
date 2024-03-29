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

# Windows fiasco
if (WIN32)
  add_custom_command(TARGET pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/deps/SFML/extlibs/bin/x64/openal32.dll $<TARGET_FILE_DIR:pong>
  )
  add_custom_command(TARGET pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:pong>/assets
  )
  set_target_properties(pong PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:pong>)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT pong)

else()
    file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
endif()


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
message("-- Using libasan")
# Enable address sanitizer and Extra warnings
target_compile_options(pong PRIVATE
    -Wall -Wextra
    -fsanitize=address
)
target_link_options(pong PRIVATE -fsanitize=address)
endif()
