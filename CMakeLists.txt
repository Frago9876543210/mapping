cmake_minimum_required(VERSION 3.11)
project(mapping)

set(CMAKE_PREFIX_PATH ../../sdk)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ModLoader

target_include_directories(mapping PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/minecraft-headers)

find_package(ModLoader REQUIRED)

# JSON
include(FetchContent)

FetchContent_Declare(json GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_library(mapping SHARED src/main.cpp)
target_link_libraries(mapping PUBLIC ModLoader PRIVATE nlohmann_json::nlohmann_json)