cmake_minimum_required(VERSION 3.17)
project(cuda)

set(CMAKE_CXX_STANDARD 14)
link_libraries(hiredis)
add_executable(cuda main.cpp conredis.cpp)