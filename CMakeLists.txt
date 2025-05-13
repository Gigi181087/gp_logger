cmake_minimum_required(VERSION 3.15)

# Projektname
project(gp_logger VERSION 1.0.0 LANGUAGES C)

# Library erstellen
add_library(gp_logger STATIC
    src/gp_logger.c
)

# Public Include-Ordner hinzufügen (nur /include !)
target_include_directories(gp_logger PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Compiler-Warnungen (optional, aber sinnvoll)
target_compile_options(gp_logger PRIVATE
    -Wall -Wextra -Wpedantic
)

# Tests (optional)
enable_testing()
add_executable(gp_logger_test
    test/test_gp_logger.c
)

target_link_libraries(gp_logger_test PRIVATE gp_logger)

add_test(NAME gp_logger_tests COMMAND gp_logger_test)
