#pragma once

#include <string>
#include "../enumIsEnough.hpp"

/// @class enum_string
/// @brief Example string-based enumeration using the enumIsEnough template.
/// 
/// Demonstrates how to create a type-safe enum with string values.
/// 
/// @note Iteration uses static begin()/end() methods since instances are class-wide.
/// Example: <code>for (auto it = enum_string::begin(); it != enum_string::end(); ++it)</code>
class enum_string :
  public enumIsEnough<enum_string, std::string> {

private:
  explicit enum_string(const std::string& Value) :
    enumIsEnough<enum_string, std::string>(Value) { }

public:
  static const enum_string enum_Alpha;
  static const enum_string enum_Beta;
  static const enum_string enum_Delta;
  static const enum_string enum_Epsilon;
  static const enum_string enum_Omega;
};
