cmake_minimum_required(VERSION 3.15)
project(enumIsEnough VERSION 1.0.0 LANGUAGES CXX)

# Create header-only interface library
add_library(enumIsEnough INTERFACE)

# Specify include directory for build and install
target_include_directories(enumIsEnough INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Require C++17 or later
target_compile_features(enumIsEnough INTERFACE cxx_std_17)

# Optional: Build examples
option(BUILD_EXAMPLES "Build example programs" ON)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Optional: Build documentation with Doxygen
option(BUILD_DOCS "Build documentation with Doxygen" OFF)

if(BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen..."
        VERBATIM
    )
endif()

# Installation rules
install(TARGETS enumIsEnough
    EXPORT enumIsEnoughConfig
)

install(FILES enumIsEnough.hpp
    DESTINATION include
)

install(EXPORT enumIsEnoughConfig
    DESTINATION lib/cmake/enumIsEnough
    NAMESPACE enumIsEnough::
)

# Generate package version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/enumIsEnoughConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/enumIsEnoughConfigVersion.cmake"
    DESTINATION lib/cmake/enumIsEnough
)

