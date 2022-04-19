cmake_minimum_required(VERSION 3.14)

project(DLLSerialPort LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(DLLSerialPort SHARED
  DLLSerialPort_global.h
  dllserialport.cpp
  dllserialport.h
)

target_link_libraries(DLLSerialPort PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(DLLSerialPort PRIVATE DLLSERIALPORT_LIBRARY)
