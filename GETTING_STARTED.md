# Getting Started with enumIsEnough

## What is enumIsEnough?

`enumIsEnough` is a C++ template library that provides intelligent, type-safe enumerations with:
- Iteration over all enum values
- Value validation
- Min/Max queries
- Instance lookup
- Support for any comparable type (int, string, custom types)

## 5-Minute Quick Start

### 1. Include the Header
```cpp
#include "enumIsEnough.hpp"
```

### 2. Create Your Enum Class
```cpp
// my_status.hpp
#pragma once
#include "enumIsEnough.hpp"

class MyStatus : public enumIsEnough<MyStatus, int> {
private:
    explicit MyStatus(const int& Value) 
        : enumIsEnough<MyStatus, int>(Value) {}
public:
    static const MyStatus OK;
    static const MyStatus ERROR;
    static const MyStatus PENDING;
};
```

### 3. Define Instances
```cpp
// my_status.cpp
#include "my_status.hpp"

// CRITICAL: Define static member in .cpp file
enumIsEnough<MyStatus, int>::instances_list 
    enumIsEnough<MyStatus, int>::s_instances;

const MyStatus MyStatus::OK(0);
const MyStatus MyStatus::ERROR(1);
const MyStatus MyStatus::PENDING(2);
```

### 4. Use It
```cpp
#include "my_status.hpp"
#include <iostream>

int main() {
    // Iterate
    for (auto it = MyStatus::begin(); it != MyStatus::end(); ++it) {
        std::cout << (*it)->Get_Value() << "\n";  // Prints: 0, 1, 2
    }
    
    // Validate
    if (MyStatus::Is_Valid_Value(1)) {
        std::cout << "1 is valid\n";  // Prints this
    }
    
    // Find
    const MyStatus* s = MyStatus::Corresponding_Enum(2);
    if (s != nullptr) {
        std::cout << "Found value 2\n";  // Prints this
    }
    
    return 0;
}
```

## Common Use Cases

### HTTP Status Codes
```cpp
class HttpStatus : public enumIsEnough<HttpStatus, int> {
private:
    explicit HttpStatus(const int& Value) 
        : enumIsEnough<HttpStatus, int>(Value) {}
public:
    static const HttpStatus OK;         // 200
    static const HttpStatus CREATED;    // 201
    static const HttpStatus BAD_REQUEST; // 400
    static const HttpStatus NOT_FOUND;  // 404
    static const HttpStatus ERROR;      // 500
};
```

### Log Levels
```cpp
class LogLevel : public enumIsEnough<LogLevel, std::string> {
private:
    explicit LogLevel(const std::string& Value) 
        : enumIsEnough<LogLevel, std::string>(Value) {}
public:
    static const LogLevel DEBUG;
    static const LogLevel INFO;
    static const LogLevel WARNING;
    static const LogLevel ERROR;
};
```

### Database Drivers
```cpp
class DatabaseDriver : public enumIsEnough<DatabaseDriver, std::string> {
private:
    explicit DatabaseDriver(const std::string& Value) 
        : enumIsEnough<DatabaseDriver, std::string>(Value) {}
public:
    static const DatabaseDriver SQLITE;
    static const DatabaseDriver POSTGRESQL;
    static const DatabaseDriver MYSQL;
};
```

## Key Concepts

### CRTP Pattern
enumIsEnough uses the "Curiously Recurring Template Pattern":
```cpp
// Your class inherits from enumIsEnough<YourClass, ValueType>
class MyEnum : public enumIsEnough<MyEnum, int> { };
```

This allows:
- Type-safe iteration
- Compile-time checks
- No virtual functions needed

### Static Methods
All methods are static (accessed from the class):
```cpp
MyEnum::Min()              // Min value
MyEnum::Max()              // Max value
MyEnum::size()             // Number of instances
MyEnum::Is_Valid_Value(5)  // Check if valid
MyEnum::Corresponding_Enum(5)  // Find by value
MyEnum::begin()            // Iterate start
MyEnum::end()              // Iterate end
```

### Instance Methods
Instance methods work on individual values:
```cpp
MyEnum e = MyEnum::OK;
int v = e.Get_Value();     // Get the value
```

## Important Rules

1. **Constructor Must Be Private**
   - Prevents creating arbitrary values
   - Enforces only static instances exist

2. **Define s_instances in .cpp**
   - Required for linking
   - One line per enum class
   - Without it: "unresolved external symbol" error

3. **Static Instances Should Be const**
   - Prevents modification
   - Ensures immutability

4. **Use Supported Types**
   - Must implement `operator<` and `operator==`
   - Works: int, string, double, custom structs

## Troubleshooting

### "undefined reference to enumIsEnough::s_instances"
**Fix**: Add this to your .cpp file:
```cpp
enumIsEnough<YourClass, ValueType>::instances_list 
    enumIsEnough<YourClass, ValueType>::s_instances;
```

### "constructor is private"
**Expected**: You can't do `MyEnum x(5);` from outside the class
**Solution**: Use static instances: `MyEnum x = MyEnum::OK;`

### Iteration returns no values
**Cause**: s_instances not defined
**Fix**: Check that you added the static member definition in .cpp

## Next Steps

1. **Read the Implementation Guide** - Complete tutorial with examples
2. **Check Quick Reference** - API summary and common patterns
3. **Study Design Patterns** - Advanced usage patterns
4. **Look at Examples** - See enum_int and enum_string
5. **Build Documentation** - `cmake .. -DBUILD_DOCS=ON`

## Documentation Files

- **README.md** - Project overview and features
- **DOCUMENTATION.md** - What was added and how to generate docs
- **pages/implementation_guide.md** - Complete step-by-step tutorial
- **pages/quick_reference.md** - API reference and common patterns
- **pages/design_patterns.md** - Advanced patterns and examples

## Performance

| Operation | Time | Notes |
|-----------|------|-------|
| Iteration | O(n) | n = number of instances |
| Validation | O(log n) | Binary search in set |
| Lookup | O(log n) | Find instance by value |
| Min/Max | O(1) | Cached pointers |

For most applications with < 100 enum values, performance is excellent.

## Requirements

- **C++ Standard**: C++11 or later
- **Dependencies**: None (standard library only)
- **Compiler**: MSVC, GCC, Clang all supported

## License

See LICENSE file for details.

## Questions?

Refer to the comprehensive documentation generated by Doxygen:
```bash
mkdir build && cd build
cmake .. -DBUILD_DOCS=ON
cmake --build . --target docs
open docs/html/index.html
```
