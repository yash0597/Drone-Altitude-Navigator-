cmake_minimum_required(VERSION 3.10)
project(HighAltitudeNavigator)

# Use C++17 (or later)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options for controlling build (you can adapt)
option(ENABLE_TESTS "Build unit tests" ON)
option(ENABLE_GUI "Build GUI components" ON)

# For debug symbols etc.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Gather sources
set(SRC_FILES
    src/main.cpp
    src/Logger.cpp
    # We'll add more .cpp files as we go along
)

# Gather headers (for IDEs, optional)
set(HEADER_FILES
    include/Logger.hpp
    # More headers to be added
)

# Create the executable
add_executable(AltitudeNavigator
    ${SRC_FILES}
    ${HEADER_FILES}  # Not strictly required, but helps some IDEs
)

# Include paths
target_include_directories(AltitudeNavigator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # We will add more subfolders as needed
)

# If we plan to add multiple source files across subfolders
# we'll keep updating SRC_FILES or do a file(GLOB ...) approach.

############
# Optional: If we want tests, we create another add_executable or use a test framework
############
if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

############
# If there's a GUI, we might need to link libraries (like Qt, etc.)
# In this project, we'll do a minimal custom approach, no external libs.
############

# We'll export compile commands for tools like clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# If you want to set up some definitions for debugging or version info
target_compile_definitions(AltitudeNavigator PRIVATE
    APP_VERSION_MAJOR=1
    APP_VERSION_MINOR=0
)

# Installation example (optional):
install(TARGETS AltitudeNavigator
    RUNTIME DESTINATION bin
)
