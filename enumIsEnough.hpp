#pragma once

#include <functional>
#include <set>

template <class T, class Tval> class enumIsEnough {
protected:
  // Constructors
  explicit enumIsEnough(const Tval& Value);

  // Predicate for finding the corresponding instance
  struct Enum_Predicate_Corresponds {
    Enum_Predicate_Corresponds(const Tval& Value) : m_value(Value) {}
    bool operator()(const enumIsEnough<T, Tval> *E) {
      return E->Get_Value() == m_value;
    }

  private:
    const Tval& m_value;
  };

  // Comparison functor for the set of instances
  struct Enum_Ptr_Less {
    bool operator()(const enumIsEnough<T, Tval>* E_1, const enumIsEnough<T, Tval>* E_2) const {
      return E_1->Get_Value() < E_2->Get_Value();
    }
  };

public:
  // Compiler-generated copy constructor and operator= are OK.
  typedef std::set<const enumIsEnough<T, Tval> *, Enum_Ptr_Less> instances_list;
  typedef typename instances_list::const_iterator const_iterator;

  // Access to int value
  Tval Get_Value(void) const { return m_value; }
  static Tval Min(void) { return (*s_instances.begin())->m_value; }
  static Tval Max(void) { return (*s_instances.rbegin())->m_value; }

  static const enumIsEnough<T, Tval> *Corresponding_Enum(Tval Value) {
    const_iterator it = find_if(s_instances.begin(), s_instances.end(),
                                Enum_Predicate_Corresponds(Value));
    return (it != s_instances.end()) ? *it : NULL;
  }

  static bool Is_Valid_Value(Tval Value) {
    return Corresponding_Enum(Value) != NULL;
  }

  // Number of elements
  static typename instances_list::size_type size(void) { return s_instances.size(); }

  // Iteration
  static const_iterator begin(void) { return s_instances.begin(); }
  static const_iterator end(void) { return s_instances.end(); }

private:
  Tval m_value;
  static instances_list s_instances;
};

template <class T, class Tval>
inline enumIsEnough<T, Tval>::enumIsEnough(const Tval& Value) : m_value(Value) {
  s_instances.insert(this);
}