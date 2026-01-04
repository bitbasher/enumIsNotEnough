#include "Test_Enum_String.hpp"

// Define static member
enumIsEnough<Test_Enum_String, std::string>::instances_list enumIsEnough<Test_Enum_String, std::string>::s_instances;

const Test_Enum_String Test_Enum_String::enum_Alpha("Alpha");
const Test_Enum_String Test_Enum_String::enum_Beta("Beta");
const Test_Enum_String Test_Enum_String::enum_Delta("Delta");
const Test_Enum_String Test_Enum_String::enum_Epsilon("Epsilon");
const Test_Enum_String Test_Enum_String::enum_Omega("Omega");
