#pragma once

#include "../enumIsEnough.hpp"

/// @file enum_int.hpp
/// @brief Example: Integer-based enumeration using enumIsEnough template

/// @class enum_int
/// @brief Example enumeration with integer values (11, 12, 18, 20, 21).
/// 
/// @details
/// This example demonstrates how to create a simple integer-based enumeration
/// using the enumIsEnough template. It shows:
/// - Creating a derived class from enumIsEnough<T, Tval>
/// - Using private constructor to prevent external instantiation
/// - Defining static const enum instances
/// - Supporting iteration, validation, and range queries
/// 
/// @par Static Instances:
/// - @c enum_11 - value: 11
/// - @c enum_12 - value: 12
/// - @c enum_18 - value: 18
/// - @c enum_20 - value: 20
/// - @c enum_21 - value: 21
/// 
/// @par Usage:
/// @code
/// // Iterate over all values
/// for (auto it = enum_int::begin(); it != enum_int::end(); ++it) {
///   int value = (*it)->Get_Value();
///   std::cout << value << std::endl;
/// }
/// 
/// // Validate a value
/// if (enum_int::Is_Valid_Value(12)) {
///   std::cout << "12 is valid" << std::endl;
/// }
/// 
/// // Get min and max
/// std::cout << "Min: " << enum_int::Min() << std::endl;
/// std::cout << "Max: " << enum_int::Max() << std::endl;
/// 
/// // Find enum by value
/// const enum_int* e = enum_int::Corresponding_Enum(18);
/// if (e != nullptr) {
///   std::cout << "Found value: " << e->Get_Value() << std::endl;
/// }
/// 
/// // Create local copies
/// enum_int local_enum(enum_int::enum_11);
/// std::cout << "Local copy value: " << local_enum.Get_Value() << std::endl;
/// @endcode
/// 
/// @see enumIsEnough for template documentation
/// @see examples/enum_string.hpp for string-based variant
class enum_int : public enumIsEnough<enum_int, int> {

private:
  /// @brief Private constructor - only allows creation via static instances
  /// @param Value The integer value for this enum instance
  explicit enum_int(const int& Value) : enumIsEnough<enum_int, int>(Value) { }

public:
  /// @name Static Enum Instances
  /// @{
  static const enum_int enum_11;  ///< Enum instance with value 11
  static const enum_int enum_12;  ///< Enum instance with value 12
  static const enum_int enum_18;  ///< Enum instance with value 18
  static const enum_int enum_20;  ///< Enum instance with value 20
  static const enum_int enum_21;  ///< Enum instance with value 21
  /// @}
};