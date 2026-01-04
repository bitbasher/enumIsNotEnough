# Integer enum example
add_executable(enum_int_example
    enum_int.cpp
    enum_int_main.cpp
)

target_link_libraries(enum_int_example PRIVATE enumIsEnough)

# String enum example
add_executable(enum_string_example
    enum_string.cpp
    enum_string_main.cpp
)

target_link_libraries(enum_string_example PRIVATE enumIsEnough)
