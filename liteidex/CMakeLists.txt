cmake_minimum_required(VERSION 3.20)

project(liteide VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Svg PrintSupport Network)
find_package(Qt5 REQUIRED COMPONENTS Widgets Svg PrintSupport Network)

add_subdirectory(src)

message(STATUS "Configuration Option Summary ---
	Target system:          ${CMAKE_SYSTEM}
    Compiler:
        - Build type:         ${CMAKE_BUILD_TYPE}
        - C compiler:         ${CMAKE_C_COMPILER}
        - Qt version:         ${QT_DEFAULT_MAJOR_VERSION}
        - Qt toolchain:       ${QT_QMAKE_EXECUTABLE}
")

