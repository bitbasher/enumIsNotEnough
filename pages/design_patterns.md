/// @page design_patterns Design Patterns and Best Practices

# Design Patterns Using enumIsEnough

This page covers advanced usage patterns and best practices when working with enumIsEnough enumerations.

## Pattern 1: Error Codes with Severity Levels

```cpp
// error.hpp
#pragma once
#include "enumIsEnough.hpp"

class ErrorCode : public enumIsEnough<ErrorCode, int> {
private:
    explicit ErrorCode(const int& Value) 
        : enumIsEnough<ErrorCode, int>(Value) {}
public:
    // Info level (100-199)
    static const ErrorCode INFO_STARTUP;
    static const ErrorCode INFO_SHUTDOWN;
    
    // Warning level (200-299)
    static const ErrorCode WARNING_SLOW;
    static const ErrorCode WARNING_DEPRECATED;
    
    // Error level (300-399)
    static const ErrorCode ERROR_INVALID_INPUT;
    static const ErrorCode ERROR_FILE_NOT_FOUND;
    
    // Critical level (400-499)
    static const ErrorCode CRITICAL_OUT_OF_MEMORY;
    static const ErrorCode CRITICAL_CRASH;
};

// Usage:
int get_severity(const ErrorCode& e) {
    int value = e.Get_Value();
    if (value < 200) return 0;  // Info
    if (value < 300) return 1;  // Warning
    if (value < 400) return 2;  // Error
    return 3;                    // Critical
}
```

## Pattern 2: State Machine

```cpp
// state.hpp
#pragma once
#include "enumIsEnough.hpp"

class State : public enumIsEnough<State, int> {
private:
    explicit State(const int& Value) 
        : enumIsEnough<State, int>(Value) {}
public:
    static const State IDLE;
    static const State LOADING;
    static const State PROCESSING;
    static const State SAVING;
    static const State ERROR;
};

// state_machine.hpp
class StateMachine {
private:
    const State* current_state;
    
public:
    bool can_transition_to(const State& next_state) const {
        // Define valid transitions
        const State& curr = *current_state;
        
        if (curr.Get_Value() == State::IDLE.Get_Value()) {
            return next_state.Get_Value() == State::LOADING.Get_Value();
        }
        if (curr.Get_Value() == State::LOADING.Get_Value()) {
            return next_state.Get_Value() == State::PROCESSING.Get_Value() ||
                   next_state.Get_Value() == State::ERROR.Get_Value();
        }
        // ... more transitions
        return false;
    }
    
    void transition_to(const State& next_state) {
        if (can_transition_to(next_state)) {
            current_state = State::Corresponding_Enum(next_state.Get_Value());
        } else {
            throw std::runtime_error("Invalid state transition");
        }
    }
};
```

## Pattern 3: Configuration Validation

```cpp
// config.hpp
#pragma once
#include "enumIsEnough.hpp"

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

// config.cpp
#include "config.hpp"

enumIsEnough<LogLevel, std::string>::instances_list 
    enumIsEnough<LogLevel, std::string>::s_instances;

const LogLevel LogLevel::DEBUG("debug");
const LogLevel LogLevel::INFO("info");
const LogLevel LogLevel::WARNING("warning");
const LogLevel LogLevel::ERROR("error");

// Validation:
bool validate_config(const std::map<std::string, std::string>& config) {
    auto log_level_it = config.find("log_level");
    if (log_level_it != config.end()) {
        const std::string& level = log_level_it->second;
        if (!LogLevel::Is_Valid_Value(level)) {
            std::cerr << "Invalid log level: " << level << "\n";
            std::cerr << "Valid values: ";
            for (auto it = LogLevel::begin(); it != LogLevel::end(); ++it) {
                std::cerr << (*it)->Get_Value() << " ";
            }
            std::cerr << "\n";
            return false;
        }
    }
    return true;
}
```

## Pattern 4: Registry Pattern

```cpp
// handler.hpp
#pragma once
#include "enumIsEnough.hpp"

class EventType : public enumIsEnough<EventType, int> {
private:
    explicit EventType(const int& Value) 
        : enumIsEnough<EventType, int>(Value) {}
public:
    static const EventType MOUSE_CLICK;
    static const EventType KEY_PRESS;
    static const EventType WINDOW_CLOSE;
};

// event_handler.hpp
#include <functional>
#include <map>

class EventHandler {
private:
    std::map<int, std::function<void()>> handlers;
    
public:
    template<typename Func>
    void register_handler(const EventType& event, Func handler) {
        handlers[event.Get_Value()] = handler;
    }
    
    void fire_event(const EventType& event) {
        auto it = handlers.find(event.Get_Value());
        if (it != handlers.end()) {
            it->second();
        }
    }
    
    void fire_all_registered_events() {
        for (auto it = EventType::begin(); it != EventType::end(); ++it) {
            fire_event(**it);
        }
    }
};
```

## Pattern 5: Database Enumeration

```cpp
// database.hpp
#pragma once
#include "enumIsEnough.hpp"

class DatabaseType : public enumIsEnough<DatabaseType, int> {
private:
    explicit DatabaseType(const int& Value) 
        : enumIsEnough<DatabaseType, int>(Value) {}
public:
    static const DatabaseType SQLITE;
    static const DatabaseType POSTGRESQL;
    static const DatabaseType MYSQL;
    static const DatabaseType ORACLE;
};

// database.cpp
#include "database.hpp"

enumIsEnough<DatabaseType, int>::instances_list 
    enumIsEnough<DatabaseType, int>::s_instances;

const DatabaseType DatabaseType::SQLITE(1);
const DatabaseType DatabaseType::POSTGRESQL(2);
const DatabaseType DatabaseType::MYSQL(3);
const DatabaseType DatabaseType::ORACLE(4);

// Usage:
std::string get_connection_string(const DatabaseType& db_type, 
                                   const std::string& host,
                                   const std::string& db_name) {
    if (!DatabaseType::Is_Valid_Value(db_type.Get_Value())) {
        throw std::invalid_argument("Unknown database type");
    }
    
    // Generate connection string based on type
    if (db_type.Get_Value() == DatabaseType::SQLITE.Get_Value()) {
        return "sqlite://" + db_name;
    }
    // ... more database types
}
```

## Pattern 6: Serialization/Deserialization

```cpp
// status.hpp
#pragma once
#include "enumIsEnough.hpp"
#include <string>

class Status : public enumIsEnough<Status, int> {
private:
    explicit Status(const int& Value) 
        : enumIsEnough<Status, int>(Value) {}
public:
    static const Status PENDING;
    static const Status ACTIVE;
    static const Status COMPLETED;
    static const Status FAILED;
    
    std::string to_string() const;
    static const Status* from_string(const std::string& str);
};

// status.cpp
#include "status.hpp"

// Serialization
std::string Status::to_string() const {
    int v = Get_Value();
    if (v == PENDING.Get_Value()) return "pending";
    if (v == ACTIVE.Get_Value()) return "active";
    if (v == COMPLETED.Get_Value()) return "completed";
    if (v == FAILED.Get_Value()) return "failed";
    return "unknown";
}

// Deserialization
const Status* Status::from_string(const std::string& str) {
    if (str == "pending") return &Status::PENDING;
    if (str == "active") return &Status::ACTIVE;
    if (str == "completed") return &Status::COMPLETED;
    if (str == "failed") return &Status::FAILED;
    return nullptr;
}

// JSON serialization example:
#include <nlohmann/json.hpp>
using json = nlohmann::json;

json serialize_status(const Status& s) {
    json j;
    j["status"] = s.to_string();
    return j;
}

Status deserialize_status(const json& j) {
    std::string str = j["status"];
    const Status* s = Status::from_string(str);
    if (!s) throw std::invalid_argument("Invalid status: " + str);
    return *s;
}
```

## Best Practices Summary

1. **Group Related Values**: Keep similar enum values together in the same class
2. **Use Meaningful Names**: Choose clear, descriptive names for enum values
3. **Document Values**: Add Doxygen comments explaining what each value means
4. **Validate Inputs**: Always use `Is_Valid_Value()` before processing external input
5. **Iterate Safely**: Remember `begin()` and `end()` are static methods
6. **Consider Ranges**: For large value spaces, consider using value ranges or bit flags
7. **Use const**: Always declare enum instances as `static const`
8. **Private Constructors**: Never make constructors public
9. **Immutable Values**: Once created, enum instances should not change
10. **Clear Semantics**: Document what values represent and when they should be used

## Performance Considerations

- **Iteration**: O(n) - acceptable for enums with <100 values
- **Lookup**: O(log n) - fast even for large value spaces
- **Creation**: One-time cost at program startup
- **Memory**: Minimal - just pointers in a set

For very large enums (1000+ values), consider alternatives like:
- Hash map for O(1) lookups (if needed)
- Separate validation function for specific value ranges
- Lazy initialization patterns

## See Also

- [Implementation Guide](implementation_guide.html) - Basic tutorial
- [Quick Reference](quick_reference.html) - API summary
