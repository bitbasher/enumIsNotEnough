/// @page quick_reference Quick Reference

# enumIsEnough Quick Reference

## API Summary

### Static Methods (Access from the class itself)

| Method | Returns | Description |
|--------|---------|-------------|
| `begin()` | `const_iterator` | Iterator to first enum instance (in sorted order) |
| `end()` | `const_iterator` | Iterator past last enum instance |
| `size()` | `size_type` | Number of enum instances |
| `Min()` | `Tval` | Minimum value |
| `Max()` | `Tval` | Maximum value |
| `Is_Valid_Value(Tval v)` | `bool` | Check if value is valid |
| `Corresponding_Enum(Tval v)` | `const T*` | Find enum by value (or nullptr) |

### Instance Methods

| Method | Returns | Description |
|--------|---------|-------------|
| `Get_Value()` | `Tval` | Get the enum instance's value |

## Template Parameters

- **T** - Your derived enum class (CRTP pattern)
- **Tval** - The value type (must support `operator<` and `operator==`)

## Quick Code Template

```cpp
// Header file: my_enum.hpp
#pragma once
#include "enumIsEnough.hpp"

class MyEnum : public enumIsEnough<MyEnum, int> {
private:
    explicit MyEnum(const int& Value) 
        : enumIsEnough<MyEnum, int>(Value) {}
public:
    static const MyEnum VALUE_A;
    static const MyEnum VALUE_B;
};

// Source file: my_enum.cpp
#include "my_enum.hpp"

enumIsEnough<MyEnum, int>::instances_list 
    enumIsEnough<MyEnum, int>::s_instances;

const MyEnum MyEnum::VALUE_A(1);
const MyEnum MyEnum::VALUE_B(2);

// Usage
#include "my_enum.hpp"

// Iterate
for (auto it = MyEnum::begin(); it != MyEnum::end(); ++it) {
    std::cout << (*it)->Get_Value() << "\n";
}

// Validate
if (MyEnum::Is_Valid_Value(1)) { /* ... */ }

// Find
const MyEnum* e = MyEnum::Corresponding_Enum(2);

// Copy
MyEnum local = MyEnum::VALUE_A;
```

## Type Support

Works with any type implementing `operator<` and `operator==`:

- `int`, `unsigned int`, `short`, `long`
- `float`, `double`
- `std::string`
- Custom structs with comparison operators
- Enums with `operator<`

## Common Patterns

### Iterate and Act
```cpp
for (auto it = Status::begin(); it != Status::end(); ++it) {
    process((*it)->Get_Value());
}
```

### Validate Input
```cpp
int code = get_status_code();
if (!Status::Is_Valid_Value(code)) {
    throw std::invalid_argument("Invalid status code");
}
```

### Initialize Container
```cpp
std::set<int> valid_values;
for (auto it = Status::begin(); it != Status::end(); ++it) {
    valid_values.insert((*it)->Get_Value());
}
```

### Find and Use
```cpp
const Status* s = Status::Corresponding_Enum(status_code);
if (s != nullptr) {
    std::cout << "Status value: " << s->Get_Value() << "\n";
} else {
    std::cout << "Invalid status\n";
}
```

## Compilation Requirements

- **C++ Standard**: C++11 or later (uses templates and `<set>`)
- **Dependencies**: Only standard library (`<set>`, `<functional>`)
- **Compiler**: MSVC, GCC, Clang all supported

## Performance Characteristics

- **Iteration**: O(n) where n = number of instances
- **Validation**: O(log n) binary search in set
- **Lookup**: O(log n) binary search in set
- **Min/Max**: O(1) amortized (cached pointers)
- **Instance creation**: O(log n) set insertion

## Thread Safety

- **Initialization**: NOT thread-safe
- **Runtime**: Thread-safe for reads after initialization
- **Recommendation**: Initialize all enum instances before launching threads

## Debugging Tips

### Linker Error: Unresolved s_instances
**Cause**: Missing static member definition in .cpp file
**Fix**: Add this line to your .cpp file:
```cpp
enumIsEnough<YourEnum, int>::instances_list 
    enumIsEnough<YourEnum, int>::s_instances;
```

### No Values in Iteration
**Cause**: s_instances is empty
**Likely cause**: Static const members not constructed yet
**Fix**: Ensure enum values are declared in .cpp file (not just header)

### Validation Always Fails
**Cause**: Value type mismatch
**Fix**: Ensure comparison uses same type as template parameter
```cpp
// Wrong: MyEnum<double> but comparing with int
int code = 5;
if (MyEnum::Is_Valid_Value(5.0)) { }  // Will never match!

// Right: Use correct type
if (MyEnum::Is_Valid_Value(5)) { }
```

## See Also

- [Implementation Guide](implementation_guide.html) - Detailed tutorial
- [Class Documentation](classEnumisEnough.html) - Full API reference
- [Examples](files.html) - Working code examples
