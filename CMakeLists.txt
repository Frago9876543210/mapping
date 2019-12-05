cmake_minimum_required(VERSION 3.0)
project(mapping)

set(CMAKE_PREFIX_PATH ../../sdk)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(include minecraft-headers)

find_package(ModLoader REQUIRED)

add_library(mapping SHARED src/main.cpp)
target_link_libraries(mapping PUBLIC ModLoader)
