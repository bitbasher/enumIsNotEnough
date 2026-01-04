/// @page implementation_guide Implementation Guide - Creating Your Own Enum

# Creating Your Own enumIsEnough Enum

This guide walks you through the steps to create a custom enumeration using the enumIsEnough template.

## Step 1: Create the Header File

Create a new header file (e.g., `status.hpp`) for your enum:

```cpp
#pragma once

#include "enumIsEnough.hpp"

/// @class Status
/// @brief Application status codes
class Status : public enumIsEnough<Status, int> {
private:
    /// Constructor is private - only allows creation via static instances
    explicit Status(const int& Value) 
        : enumIsEnough<Status, int>(Value) { }

public:
    /// Static enum instances
    static const Status OK;
    static const Status PENDING;
    static const Status ERROR;
    static const Status TIMEOUT;
};
```

### Key Points:
1. **Private Constructor**: This prevents users from creating arbitrary `Status` values
2. **Explicit Call to Base Constructor**: Passes the value to enumIsEnough constructor
3. **Static Const Members**: Define your enum values as static const class members
4. **CRTP Pattern**: Class derives from `enumIsEnough<YourClass, ValueType>`

## Step 2: Create the Implementation File

Create a corresponding `.cpp` file (e.g., `status.cpp`):

```cpp
#include "status.hpp"

/// CRITICAL: Define the static instances list
/// This MUST appear in exactly one .cpp file!
enumIsEnough<Status, int>::instances_list 
    enumIsEnough<Status, int>::s_instances;

/// Define each enum instance
const Status Status::OK(0);
const Status Status::PENDING(1);
const Status Status::ERROR(2);
const Status Status::TIMEOUT(3);
```

### Key Points:
1. **Static Member Definition**: The `s_instances` line is **required** - without it, you'll get linker errors
2. **Value Types**: Values don't need to be sequential (0, 1, 2, 3) - they can be any comparable values
3. **Value Types Can Be Anything**: Use hex codes, random numbers, or any int that makes sense

## Step 3: Use Your Enum

```cpp
#include "status.hpp"
#include <iostream>

int main() {
    // Iterate over all enum values
    std::cout << "Status values:\n";
    for (auto it = Status::begin(); it != Status::end(); ++it) {
        std::cout << "  Value: " << (*it)->Get_Value() << "\n";
    }

    // Validate a status code
    int code = 1;
    if (Status::Is_Valid_Value(code)) {
        std::cout << code << " is a valid status\n";
    }

    // Get min/max values
    std::cout << "Min status: " << Status::Min() << "\n";
    std::cout << "Max status: " << Status::Max() << "\n";

    // Find enum by value
    const Status* status = Status::Corresponding_Enum(2);
    if (status != nullptr) {
        std::cout << "Found status with value 2\n";
    }

    // Create local variables
    Status my_status(Status::OK);
    std::cout << "My status value: " << my_status.Get_Value() << "\n";

    // Assign to other instance
    my_status = Status::ERROR;
    std::cout << "Updated status value: " << my_status.Get_Value() << "\n";

    return 0;
}
```

## Advanced: Using Non-Integer Types

The enumIsEnough template works with any type that implements `operator<` and `operator==`.

### Example: String-Based Enum

```cpp
#pragma once

#include <string>
#include "enumIsEnough.hpp"

class Priority : public enumIsEnough<Priority, std::string> {
private:
    explicit Priority(const std::string& Value) 
        : enumIsEnough<Priority, std::string>(Value) { }

public:
    static const Priority LOW;
    static const Priority MEDIUM;
    static const Priority HIGH;
};
```

Implementation:
```cpp
#include "priority.hpp"

enumIsEnough<Priority, std::string>::instances_list 
    enumIsEnough<Priority, std::string>::s_instances;

const Priority Priority::LOW("low");
const Priority Priority::MEDIUM("medium");
const Priority Priority::HIGH("high");
```

Usage:
```cpp
// Works just like integers!
for (auto it = Priority::begin(); it != Priority::end(); ++it) {
    std::cout << (*it)->Get_Value() << "\n";  // Prints: "high", "low", "medium" (sorted)
}

if (Priority::Is_Valid_Value("low")) {
    std::cout << "Valid priority\n";
}
```

### Example: Custom Type

Any type with `operator<` works:

```cpp
struct Date {
    int year, month, day;
    
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    
    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }
};

class Release : public enumIsEnough<Release, Date> { /* ... */ };
```

## Common Pitfalls

### 1. Forgetting s_instances Definition
**Error**: Linker error "unresolved external symbol s_instances"
**Fix**: Add this line to your .cpp file:
```cpp
enumIsEnough<YourEnum, YourType>::instances_list 
    enumIsEnough<YourEnum, YourType>::s_instances;
```

### 2. Using Non-const Static Members
**Wrong**:
```cpp
static Status my_status;  // NOT const - wrong!
```

**Right**:
```cpp
static const Status my_status;  // Always use const!
```

### 3. Making Constructor Public
**Wrong**:
```cpp
public:
    explicit MyEnum(const int& Value) { }  // Public - anyone can create values!
```

**Right**:
```cpp
private:
    explicit MyEnum(const int& Value) { }  // Private - only static instances
```

## Tips and Best Practices

1. **Use Meaningful Names**: Choose names that describe the value
   - Good: `Status::PENDING`, `Priority::HIGH`
   - Bad: `Status::X`, `Priority::P1`

2. **Group Related Values**: Put similar enums in the same namespace
   ```cpp
   namespace http {
       class StatusCode : public enumIsEnough<StatusCode, int> { /* ... */ };
   }
   ```

3. **Document Value Meanings**: Use comments to explain what values mean
   ```cpp
   static const Status OK;       ///< Operation succeeded (0)
   static const Status PENDING;  ///< Operation in progress (1)
   static const Status ERROR;    ///< Operation failed (2)
   ```

4. **Handle Validation**: Always check `Is_Valid_Value()` before using input values
   ```cpp
   int code = get_status_from_api();
   if (Status::Is_Valid_Value(code)) {
       // Safe to use
   } else {
       // Invalid status code - log error
   }
   ```

5. **Use Iteration for Initialization**: Initialize containers with all valid values
   ```cpp
   std::vector<int> valid_statuses;
   for (auto it = Status::begin(); it != Status::end(); ++it) {
       valid_statuses.push_back((*it)->Get_Value());
   }
   ```

## Complete Example

See the `examples/` directory for complete, working examples:
- [enum_int.hpp](../examples/enum_int.hpp) and [enum_int.cpp](../examples/enum_int.cpp) - Integer enum
- [enum_string.hpp](../examples/enum_string.hpp) and [enum_string.cpp](../examples/enum_string.cpp) - String enum
