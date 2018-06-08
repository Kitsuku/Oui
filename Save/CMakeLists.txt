cmake_minimum_required(VERSION 3.10)
include_directories(include include/characters include/objects json-develop/single_include/nlohmann)
add_executable(mySave ./src/ACharacter_methods.cpp ./src/AObject_methods.cpp ./src/main.cpp ./src/Map.cpp)

