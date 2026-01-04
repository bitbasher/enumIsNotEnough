#pragma once

#include "../enumIsEnough.hpp"

/// @class enum_int
/// @brief Example integer-based enumeration using the enumIsEnough template.
/// 
/// Demonstrates how to create a type-safe enum with compile-time and runtime
/// validation, iteration support, and min/max functionality.
/// 
/// @note Iteration uses static begin()/end() methods since instances are class-wide.
/// Example: <code>for (auto it = enum_int::begin(); it != enum_int::end(); ++it)</code>
class enum_int : public enumIsEnough<enum_int, int> {

private:
  explicit enum_int(const int& Value) : enumIsEnough<enum_int, int>(Value) { }

public:
  static const enum_int enum_11;
  static const enum_int enum_12;
  static const enum_int enum_18;
  static const enum_int enum_20;
  static const enum_int enum_21;
};