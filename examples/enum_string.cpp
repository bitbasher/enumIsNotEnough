#include "enum_string.hpp"

// Define static member
enumIsEnough<enum_string, std::string>::instances_list enumIsEnough<enum_string, std::string>::s_instances;

const enum_string enum_string::enum_Alpha("Alpha");
const enum_string enum_string::enum_Beta("Beta");
const enum_string enum_string::enum_Delta("Delta");
const enum_string enum_string::enum_Epsilon("Epsilon");
const enum_string enum_string::enum_Omega("Omega");
