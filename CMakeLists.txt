cmake_minimum_required (VERSION 3.4)
project(Misc CXX)

option(${PROJECT_NAME}_BUILD_TESTS "Build unit tests for ${PROJECT_NAME} if BUILD_TESTING is ON" FALSE)
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

#set(${PROJECT_NAME}_VERSION_MAJOR 0)
#set(${PROJECT_NAME}_VERSION_MINOR 1)
#configure_file("${PROJECT_SOURCE_DIR}/Version.h.in" "${PROJECT_BINARY_DIR}/Version.h")

set(PUBLIC_INCLUDE_PATHS
    include
)

set(PRIVATE_INCLUDE_PATHS
    .
    include/Misc
)

set(SOURCES
    include/Misc/AfxAssert.h
    include/Misc/Assert.h
    include/Misc/Etc.h
    include/Misc/Exceptions.h
    include/Misc/PathName.h
    include/Misc/Random.h
    include/Misc/Singleton.h
    include/Misc/Trace.h
    
    Random.cpp
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
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

if(${PROJECT_NAME}_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
