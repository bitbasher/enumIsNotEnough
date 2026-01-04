#pragma once

#include <functional>
#include <set>

/// @file enumIsEnough.hpp
/// @brief Header-only template library for type-safe enumeration with iteration and validation.
/// @author Based on "When enum Just Isn't Enough" by Yves Meynard (2003)
/// @version 1.0.0

/// @class enumIsEnough
/// @brief Template base class for creating intelligent, type-safe enumerations.
/// 
/// @details
/// enumIsEnough provides a template-based approach to creating type-safe enumerations
/// that support:
/// - Iteration over all enum instances via begin() and end()
/// - Value validation via Is_Valid_Value()
/// - Min/Max value queries
/// - Lookup of enum instance from value via Corresponding_Enum()
/// - Automatic instance registration in a sorted container
/// 
/// The template uses the Curiously Recurring Template Pattern (CRTP), where:
/// - @c T is the derived enum class itself
/// - @c Tval is the underlying value type (must support operator< and operator==)
/// 
/// @par Usage Example:
/// @code
/// class Color : public enumIsEnough<Color, int> {
///   private:
///     explicit Color(const int& Value) : enumIsEnough<Color, int>(Value) {}
///   public:
///     static const Color Red;
///     static const Color Green;
///     static const Color Blue;
/// };
/// 
/// // In .cpp file:
/// enumIsEnough<Color, int>::instances_list enumIsEnough<Color, int>::s_instances;
/// const Color Color::Red(0xFF0000);
/// const Color Color::Green(0x00FF00);
/// const Color Color::Blue(0x0000FF);
/// @endcode
/// 
/// @par Thread Safety:
/// Not thread-safe during initialization. All enum instances must be constructed
/// before concurrent access. Read operations are safe once initialized.
/// 
/// @tparam T The derived enum class (CRTP pattern)
/// @tparam Tval The underlying value type (must be comparable and equality-testable)
template <class T, class Tval> class enumIsEnough {
protected:
  /// @brief Protected constructor - only derived classes can construct instances.
  /// @param Value The value for this enum instance
  /// @details Each derived class should use this constructor in its private constructor
  /// to create static const instances. The instance is automatically registered in
  /// s_instances upon construction.
  explicit enumIsEnough(const Tval& Value);

  /// @brief Predicate functor for finding enum instances by value.
  /// @details Used internally by find_if to locate an enum instance matching a given value.
  struct Enum_Predicate_Corresponds {
    /// @brief Constructor
    /// @param Value The value to search for
    Enum_Predicate_Corresponds(const Tval& Value) : m_value(Value) {}
    
    /// @brief Equality comparison operator
    /// @param E Pointer to enum instance to test
    /// @return true if E's value matches the search value
    bool operator()(const enumIsEnough<T, Tval> *E) {
      return E->Get_Value() == m_value;
    }

  private:
    const Tval& m_value; ///< The value being searched for
  };

  /// @brief Comparison functor for maintaining sorted set of enum instances.
  /// @details Required for std::set to sort pointers by their values rather than
  /// by pointer address. Essential for Min(), Max(), and iteration to work correctly.
  struct Enum_Ptr_Less {
    /// @brief Less-than comparison operator for enum pointers
    /// @param E_1 First enum instance pointer
    /// @param E_2 Second enum instance pointer
    /// @return true if E_1's value is less than E_2's value
    bool operator()(const enumIsEnough<T, Tval>* E_1, const enumIsEnough<T, Tval>* E_2) const {
      return E_1->Get_Value() < E_2->Get_Value();
    }
  };

public:
  // Compiler-generated copy constructor and operator= are OK.
  
  /// @brief Set container type for storing and sorting enum instances
  typedef std::set<const enumIsEnough<T, Tval> *, Enum_Ptr_Less> instances_list;
  
  /// @brief Const iterator type for iterating over enum instances
  typedef typename instances_list::const_iterator const_iterator;

  /// @brief Get the underlying value of this enum instance
  /// @return The value associated with this enum instance
  Tval Get_Value(void) const { return m_value; }
  
  /// @brief Get the minimum value among all enum instances
  /// @return The smallest value in the enumeration
  /// @throws std::exception if no instances exist
  static Tval Min(void) { return (*s_instances.begin())->m_value; }
  
  /// @brief Get the maximum value among all enum instances
  /// @return The largest value in the enumeration
  /// @throws std::exception if no instances exist
  static Tval Max(void) { return (*s_instances.rbegin())->m_value; }

  /// @brief Find the enum instance corresponding to a given value
  /// @param Value The value to search for
  /// @return Pointer to the enum instance with the matching value, or NULL if not found
  static const enumIsEnough<T, Tval> *Corresponding_Enum(Tval Value) {
    const_iterator it = find_if(s_instances.begin(), s_instances.end(),
                                Enum_Predicate_Corresponds(Value));
    return (it != s_instances.end()) ? *it : NULL;
  }

  /// @brief Check if a value corresponds to a valid enum instance
  /// @param Value The value to validate
  /// @return true if Value matches an enum instance, false otherwise
  static bool Is_Valid_Value(Tval Value) {
    return Corresponding_Enum(Value) != NULL;
  }

  /// @brief Get the number of enum instances
  /// @return Count of all registered enum instances
  static typename instances_list::size_type size(void) { return s_instances.size(); }

  /// @brief Get iterator to the first enum instance (in sorted order)
  /// @return Const iterator to the minimum-valued instance
  /// @details Instances are iterated in sorted order by value
  static const_iterator begin(void) { return s_instances.begin(); }
  
  /// @brief Get iterator past the last enum instance
  /// @return Const iterator to position after the maximum-valued instance
  static const_iterator end(void) { return s_instances.end(); }

private:
  Tval m_value; ///< The underlying value for this instance
  
  /// @brief Static set of all registered enum instances (sorted)
  /// @details Must be explicitly instantiated in the derived class's .cpp file.
  /// Example: @code enumIsEnough<MyEnum, int>::instances_list enumIsEnough<MyEnum, int>::s_instances; @endcode
  static instances_list s_instances;
};

/// @brief Constructor implementation - automatically registers instance in s_instances
/// @tparam T The derived enum class
/// @tparam Tval The underlying value type
/// @param Value The value for this enum instance
template <class T, class Tval>
inline enumIsEnough<T, Tval>::enumIsEnough(const Tval& Value) : m_value(Value) {
  s_instances.insert(this);
}