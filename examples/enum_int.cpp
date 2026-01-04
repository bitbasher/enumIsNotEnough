/// @file enum_int.cpp
/// @brief Implementation of enum_int enumeration

#include "enum_int.hpp"

/// @brief Explicit instantiation of the static instances list for enum_int
/// @details This line MUST appear in exactly one .cpp file for each derived enum class.
/// It allocates storage for the static set that holds all enum instances.
/// Without this line, you'll get linker errors about undefined s_instances.
enumIsEnough<enum_int, int>::instances_list enumIsEnough<enum_int, int>::s_instances;

/// @brief Static instance with value 11
/// @details Constructed at program startup before main() executes.
/// Automatically registered in s_instances via enumIsEnough constructor.
const enum_int enum_int::enum_11(11);

/// @brief Static instance with value 12
const enum_int enum_int::enum_12(12);

/// @brief Static instance with value 18
const enum_int enum_int::enum_18(18);

/// @brief Static instance with value 20
const enum_int enum_int::enum_20(20);

/// @brief Static instance with value 21
const enum_int enum_int::enum_21(21);


