cmake_minimum_required(VERSION 3.10)
project(FiveLang VERSION 0.1)

add_executable(FiveLang Debugger.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(FiveLang PRIVATE ./Headers)