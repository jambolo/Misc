cmake_minimum_required (VERSION 3.10)
project(Misc VERSION 1.1.0 LANGUAGES CXX)

#configure_file("${PROJECT_SOURCE_DIR}/Version.h.in" "${PROJECT_BINARY_DIR}/Version.h")

option(BUILD_SHARED_LIBS "Build libraries as DLLs" FALSE)

set(${PROJECT_NAME}_DOXYGEN_OUTPUT_DIRECTORY "" CACHE PATH "Doxygen output directory (empty to disable)")
if(${PROJECT_NAME}_DOXYGEN_OUTPUT_DIRECTORY)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_OUTPUT_DIRECTORY ${${PROJECT_NAME}_DOXYGEN_OUTPUT_DIRECTORY})
        configure_file(Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile)
        add_custom_target(doxygen ALL ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM
            SOURCES ${PROJECT_BINARY_DIR}/Doxyfile
        )
    endif(DOXYGEN_FOUND)
endif()

set(PUBLIC_INCLUDE_PATHS
    $<INSTALL_INTERFACE:include>    
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set(PRIVATE_INCLUDE_PATHS
    .
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Misc
)

set(SOURCES
    include/Misc/AfxAssert.h
    include/Misc/Assertx.h
    include/Misc/Base64.h
    include/Misc/CommandLineList.h
    include/Misc/Deferred.h
    include/Misc/Etc.h
    include/Misc/Exceptions.h
    include/Misc/FrameAllocator.h
    include/Misc/FrameRateCalculator.h
    include/Misc/PathName.h
    include/Misc/Pool.h
    include/Misc/Singleton.h
    include/Misc/Trace.h
    
    Base64.cpp
    CommandLineList.cpp
    FrameAllocator.cpp
    FrameRateCalculator.cpp
    Pool.cpp
    Trace.cpp
)
source_group(Sources FILES ${SOURCES})

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDE_PATHS} PRIVATE ${PRIVATE_INCLUDE_PATHS})
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        -DNOMINMAX
        -DWIN32_LEAN_AND_MEAN
        -DVC_EXTRALEAN
        -D_CRT_SECURE_NO_WARNINGS
        -D_SECURE_SCL=0
        -D_SCL_SECURE_NO_WARNINGS
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    message(STATUS "Testing is enabled. Turn on BUILD_TESTING to build tests.")
    if(BUILD_TESTING)
        add_subdirectory(test)
    endif()
endif()

# Installation

add_library(Misc::Misc ALIAS Misc)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/Misc)

install(TARGETS Misc
    EXPORT misc-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT misc-targets
    FILE MiscTargets.cmake
    NAMESPACE Misc::
    DESTINATION ${INSTALL_CONFIGDIR}
)

#This is required so that the exported target has the name Misc and not misc
# set_target_properties(misc PROPERTIES EXPORT_NAME Misc)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MiscConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/MiscConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MiscConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/MiscConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MiscConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

# Exporting from the build tree
export(EXPORT misc-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/MiscTargets.cmake NAMESPACE Misc::)

#Register package in user's package registry
export(PACKAGE Misc)
