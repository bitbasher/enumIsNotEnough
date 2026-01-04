#pragma once

#include <string>
#include "../enumIsEnough.hpp"

/// @file enum_string.hpp
/// @brief Example: String-based enumeration using enumIsEnough template

/// @class enum_string
/// @brief Example enumeration with string values (Alpha, Beta, Delta, Epsilon, Omega).
/// 
/// @details
/// This example demonstrates how to create a string-based enumeration
/// using the enumIsEnough template with std::string as the value type.
/// It shows how enumIsEnough is not limited to integer values.
/// 
/// @par Static Instances:
/// - @c enum_Alpha - value: "Alpha"
/// - @c enum_Beta - value: "Beta"
/// - @c enum_Delta - value: "Delta"
/// - @c enum_Epsilon - value: "Epsilon"
/// - @c enum_Omega - value: "Omega"
/// 
/// @par Usage:
/// @code
/// // Iterate over all string values
/// for (auto it = enum_string::begin(); it != enum_string::end(); ++it) {
///   std::string value = (*it)->Get_Value();
///   std::cout << value << std::endl;
/// }
/// 
/// // Validate a string value
/// if (enum_string::Is_Valid_Value("Beta")) {
///   std::cout << "Beta is valid" << std::endl;
/// }
/// 
/// // Get min and max (lexicographically)
/// std::cout << "Min: " << enum_string::Min() << std::endl;
/// std::cout << "Max: " << enum_string::Max() << std::endl;
/// 
/// // Create local copies
/// enum_string local_enum(enum_string::enum_Alpha);
/// std::cout << "Local copy value: " << local_enum.Get_Value() << std::endl;
/// @endcode
/// 
/// @see enumIsEnough for template documentation
/// @see examples/enum_int.hpp for integer-based variant
class enum_string :
  public enumIsEnough<enum_string, std::string> {

private:
  /// @brief Private constructor - only allows creation via static instances
  /// @param Value The string value for this enum instance
  explicit enum_string(const std::string& Value) :
    enumIsEnough<enum_string, std::string>(Value) { }

public:
  /// @name Static Enum Instances
  /// @{
  static const enum_string enum_Alpha;     ///< Enum instance with value "Alpha"
  static const enum_string enum_Beta;      ///< Enum instance with value "Beta"
  static const enum_string enum_Delta;     ///< Enum instance with value "Delta"
  static const enum_string enum_Epsilon;   ///< Enum instance with value "Epsilon"
  static const enum_string enum_Omega;     ///< Enum instance with value "Omega"
  /// @}
};
