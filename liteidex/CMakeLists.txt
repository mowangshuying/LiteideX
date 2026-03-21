cmake_minimum_required(VERSION 3.20)

project(liteide VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#${CMAKE_BINARY_DIR}/liteide/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/liteide/lib/liteide/plugins")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/liteide/lib/liteide/plugins")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/liteide/lib/liteide")

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Svg PrintSupport Network Xml)
find_package(Qt5 REQUIRED COMPONENTS Widgets Svg PrintSupport Network Xml)

add_subdirectory(src)

message(STATUS "Configuration Option Summary ---
	Target system:          ${CMAKE_SYSTEM}
    Compiler:
        - Build type:         ${CMAKE_BUILD_TYPE}
        - C compiler:         ${CMAKE_C_COMPILER}
        - Qt version:         ${QT_DEFAULT_MAJOR_VERSION}
        - Qt toolchain:       ${QT_QMAKE_EXECUTABLE}
")

