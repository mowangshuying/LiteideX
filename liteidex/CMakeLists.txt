cmake_minimum_required(VERSION 3.20)

project(liteide VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


### the plugin output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins")

#### the plugin output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins")

#### the lib;
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/liteide/lib/liteide")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/liteide/lib/liteide")


find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Svg PrintSupport Network Xml Sql)
find_package(Qt5 REQUIRED COMPONENTS Widgets Svg PrintSupport Network Xml Sql)

add_subdirectory(src)

# cpack settings
set(CPACK_PACKAGE_NAME "liteide")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "LiteIDE - A simple, open source, cross-platform Go IDE")
set(CPACK_PACKAGE_VENDOR "liteide team")
set(CPACK_PACKAGE_CONTACT "visualfc@gmail.com")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.LGPL")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/../README.md")

# set CPack package name format.
set(CPACK_PACKAGE_FILE_NAME liteide)

# Windows specific configuration
if(WIN32)
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_NSIS_DISPLAY_NAME "LiteIDE")
    set(CPACK_NSIS_PACKAGE_NAME "LiteIDE")
    set(CPACK_NSIS_HELP_LINK "https://github.com/visualfc/liteide")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/visualfc/liteide")
    set(CPACK_NSIS_MODIFY_PATH ON)
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_DMG_VOLUME_NAME "LiteIDE")
    set(CPACK_DMG_FORMAT "UDBZ")
else()
    # Linux
    set(CPACK_GENERATOR "TGZ")
    find_program(DPKG_PROGRAM dpkg)
    if(DPKG_PROGRAM)
        list(APPEND CPACK_GENERATOR "DEB")
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "liteide team")
        set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
    endif()
endif()

# install rule;

# install bin & dll.
install(DIRECTORY "${CMAKE_SOURCE_DIR}/liteide/bin"
        DESTINATION "."
        USE_SOURCE_PERMISSIONS
        PATTERN "*.ilk" EXCLUDE
        PATTERN "*.pdb" EXCLUDE
        PATTERN "*.exp" EXCLUDE
        PATTERN "*.lib" EXCLUDE
        PATTERN "*.obj" EXCLUDE
)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/deploy/"
        DESTINATION "./share/liteide"
        PATTERN ".git*" EXCLUDE
)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/liteide/lib"
        DESTINATION "."
        USE_SOURCE_PERMISSIONS
        PATTERN "*.ilk" EXCLUDE
        PATTERN "*.pdb" EXCLUDE
        PATTERN "*.exp" EXCLUDE
        PATTERN "*.lib" EXCLUDE
        PATTERN "*.obj" EXCLUDE
)

install(FILES "${CMAKE_SOURCE_DIR}/LICENSE.LGPL"
              "${CMAKE_SOURCE_DIR}/LGPL_EXCEPTION.TXT"
              "${CMAKE_SOURCE_DIR}/../README.md"
        DESTINATION "."
)
include(CPack)

message(STATUS "Configuration Option Summary ---
	Target system:          ${CMAKE_SYSTEM}
    Compiler:
        - Build type:         ${CMAKE_BUILD_TYPE}
        - C compiler:         ${CMAKE_C_COMPILER}
        - Qt version:         ${QT_DEFAULT_MAJOR_VERSION}
        - Qt toolchain:       ${QT_QMAKE_EXECUTABLE}
        - CPack Generator:    ${CPACK_GENERATOR}
")
