cmake_minimum_required (VERSION 3.8)
project(misc CXX)

option(BUILD_SHARED_LIBS "Build libraries as DLLs" FALSE)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doxygen ALL
        ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        SOURCES Doxyfile
    )
endif(DOXYGEN_FOUND)

#set(misc_VERSION_MAJOR 0)
#set(misc_VERSION_MINOR 1)
#configure_file("${PROJECT_SOURCE_DIR}/Version.h.in" "${PROJECT_BINARY_DIR}/Version.h")

set(PUBLIC_INCLUDE_PATHS
    include
)

set(SOURCES
    include/misc/AfxAssert.h
    include/misc/Assert.h
    include/misc/Etc.h
    include/misc/exceptions.h
    include/misc/PathName.h
    include/misc/Random.h
    include/misc/Random.inl
    include/misc/Singleton.h
    include/misc/trace.h
    
    Random.cpp
    trace.cpp
)

add_library(misc ${SOURCES})
target_compile_definitions(misc
    PRIVATE
        -DNOMINMAX
        -DWIN32_LEAN_AND_MEAN
        -DVC_EXTRALEAN
        -D_CRT_SECURE_NO_WARNINGS
        -D_SECURE_SCL=0
        -D_SCL_SECURE_NO_WARNINGS
)
target_include_directories(misc PUBLIC ${PUBLIC_INCLUDE_PATHS})

add_subdirectory(unit-test)