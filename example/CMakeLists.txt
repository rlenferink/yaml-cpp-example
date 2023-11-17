cmake_minimum_required (VERSION 3.19)
project (yaml-cpp-example CXX)


add_executable(example example.cpp)

target_include_directories(example PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../yaml-cpp-install/include"
)
target_link_libraries(example PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../yaml-cpp-install/lib64/libyaml-cpp.a"
)
