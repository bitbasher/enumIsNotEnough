/// @file enum_string.cpp
/// @brief Implementation of enum_string enumeration

#include "enum_string.hpp"

/// @brief Explicit instantiation of the static instances list for enum_string
/// @details This line MUST appear in exactly one .cpp file for each derived enum class.
/// It allocates storage for the static set that holds all enum instances.
enumIsEnough<enum_string, std::string>::instances_list enumIsEnough<enum_string, std::string>::s_instances;

/// @brief Static instance with value "Alpha"
/// @details Constructed at program startup before main() executes.
const enum_string enum_string::enum_Alpha("Alpha");

/// @brief Static instance with value "Beta"
const enum_string enum_string::enum_Beta("Beta");

/// @brief Static instance with value "Delta"
const enum_string enum_string::enum_Delta("Delta");

/// @brief Static instance with value "Epsilon"
const enum_string enum_string::enum_Epsilon("Epsilon");

/// @brief Static instance with value "Omega"
const enum_string enum_string::enum_Omega("Omega");
