cmake_minimum_required(VERSION 3.20)
project(oop_labs LANGUAGES CXX)
if(NOT WIN32 OR NOT MSVC)
    message(FATAL_ERROR "Use Windows and Microsoft Visual C++ (Visual Studio).")
endif()
add_executable(oop_labs src/main.cpp
    src/lab1.cpp
    src/lab2.cpp
    src/lab3a.cpp
    src/lab3b.cpp
    src/lab4.cpp
    src/lab5.cpp
    src/lab6.cpp
    src/lab7a.cpp
    src/lab7b.cpp
)
target_compile_features(oop_labs PRIVATE cxx_std_17)
target_compile_options(oop_labs PRIVATE /utf-8 /W4 /EHsc)
target_compile_definitions(oop_labs PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
set_property(TARGET oop_labs PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
