cmake_minimum_required(VERSION 3.15)

project("Example Executable"
    VERSION 0.1
    DESCRIPTION "A project that builds Barrel as an external dependency"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "<ABSOLUTE_PATH_TO_BARREL_INSTALLATION_DIR>")

find_package(Barrel CONFIG REQUIRED)

# This project intends to produce an executable ultimately
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    main.cpp
)

# Note the "Barrel" namespace
target_link_libraries(${PROJECT_NAME} PRIVATE Barrel::Barrel)