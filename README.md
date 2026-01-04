# enumIsEnough

A C++ template class that provides intelligent enumeration capabilities with type-safe iteration, validation, and range operations.

---

**Original Concept:** "When enum Just Isn't Enough: Enumeration Classes for C++" by Yves Meynard, 2003  
_See [README_original.md](README_original.md) for the original article._

---

## Overview

`enumIsEnough` is a header-only template library that enhances traditional C++ enums by providing:
- **Type-safe iteration** over all enum values
- **Value validation** to check if a value is valid for the enum
- **Min/Max operations** to get the range of enum values
- **Automatic registration** of all enum instances
- **Generic value types** - works with `int`, `std::string`, or any comparable type

## Features

- Header-only template library (just include `enumIsEnough.hpp`)
- No external dependencies beyond standard C++ library
- Requires C++17 or later
- Automatically maintains a sorted set of all enum instances
- Supports any value type that implements `operator<` and `operator==`

## Quick Start

### 1. Define Your Enum Class

Create a derived class that inherits from `enumIsEnough<YourClass, ValueType>`:

```cpp
#include "enumIsEnough.hpp"

class Color : public enumIsEnough<Color, int> {
private:
    // Constructor must be private to prevent external instantiation
    explicit Color(const int& Value) : enumIsEnough<Color, int>(Value) {}

public:
    // Define your enum instances as static const members
    static const Color Red;
    static const Color Green;
    static const Color Blue;
};
```

### 2. Instantiate Static Members

In your `.cpp` file, define the static member list and instances:

```cpp
#include "color.hpp"

// Required: Instantiate the static instances list
enumIsEnough<Color, int>::instances_list enumIsEnough<Color, int>::s_instances;

// Define your enum values
const Color Color::Red(0xFF0000);
const Color Color::Green(0x00FF00);
const Color Color::Blue(0x0000FF);
```

### 3. Use Your Enum

```cpp
#include <iostream>
#include "color.hpp"

int main() {
    // Iterate over all enum values
    std::cout << "All colors (" << Color::size() << " total):\n";
    for (auto it = Color::begin(); it != Color::end(); ++it) {
        std::cout << "  Color value: " << (*it)->Get_Value() << "\n";
    }

    // Get min/max values
    std::cout << "Min color: " << Color::Min() << "\n";
    std::cout << "Max color: " << Color::Max() << "\n";

    // Validate values
    int testValue = 0xFF0000;
    if (Color::Is_Valid_Value(testValue)) {
        std::cout << testValue << " is a valid color\n";
    }

    // Get corresponding enum instance
    const Color* c = Color::Corresponding_Enum(0x00FF00);
    if (c != nullptr) {
        std::cout << "Found color with value: " << c->Get_Value() << "\n";
    }

    return 0;
}
```

## API Reference

### Instance Methods

- `Tval Get_Value() const` - Returns the value of this enum instance

### Static Methods

- `static Tval Min()` - Returns the minimum enum value
- `static Tval Max()` - Returns the maximum enum value
- `static size_type size()` - Returns the number of enum instances
- `static const_iterator begin()` - Returns iterator to first enum instance
- `static const_iterator end()` - Returns iterator past last enum instance
- `static bool Is_Valid_Value(Tval value)` - Checks if a value corresponds to a valid enum instance
- `static const T* Corresponding_Enum(Tval value)` - Returns pointer to enum instance with given value (or `nullptr`)

## Using with CMake

### Option 1: Add as Subdirectory

```cmake
add_subdirectory(path/to/enumIsEnough)
target_link_libraries(your_target PRIVATE enumIsEnough)
```

### Option 2: Install and Use find_package

Build and install:
```bash
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/your/install/path
cmake --build .
cmake --install .
```

Use in your project:
```cmake
find_package(enumIsEnough REQUIRED)
target_link_libraries(your_target PRIVATE enumIsEnough::enumIsEnough)
```

## Examples

See the `examples/` directory for complete working examples:

- **enum_int** - Integer-based enumeration (values: 11, 12, 18, 20, 21)
- **enum_string** - String-based enumeration (values: "Alpha", "Beta", "Delta", "Epsilon", "Omega")

Build examples:
```bash
mkdir build && cd build
cmake .. -DBUILD_EXAMPLES=ON
cmake --build .
# Windows
.\examples\Debug\enum_int_example.exe
.\examples\Debug\enum_string_example.exe
# Linux/Mac
./examples/enum_int_example
./examples/enum_string_example
```

## Requirements

- C++17 or later
- Standard C++ library with `<set>` and `<functional>` support
- CMake 3.15 or later (for building with CMake)

## Pattern Explanation

The `enumIsEnough` class uses the Curiously Recurring Template Pattern (CRTP):
- Template parameter `T` is the derived enum class itself
- Template parameter `Tval` is the type of values stored (int, string, etc.)
- Protected constructor allows derived classes to create instances
- Static `s_instances` set automatically registers all instances at construction
- Each derived class gets its own separate instance list

## Thread Safety

The library is **not thread-safe** during initialization. Ensure all enum instances are constructed before any concurrent access. Once initialized, all read operations (iteration, validation, lookup) are safe for concurrent use.

## License

See LICENSE file for details.
