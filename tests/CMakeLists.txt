# tests/CMakeLists.txt

# If you want to build test executables, do it here.
# For example:
add_executable(MyFirstTest
    test_PathPlanner.cpp
    # other test files...
)

target_include_directories(MyFirstTest PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# (Optional) If you need to link libraries or your main code, do it here.
# e.g.:
# target_link_libraries(MyFirstTest PRIVATE AltitudeNavigatorLib)

# Now register it with CTest so we can run it via `ctest`
add_test(NAME MyFirstTest COMMAND MyFirstTest)
