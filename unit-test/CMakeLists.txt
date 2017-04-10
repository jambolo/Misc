cmake_minimum_required (VERSION 3.4)

set(INCLUDE_PATHS
    ${PROJECT_SOURCE_DIR}/include
)

set(SOURCES
    unit-test.cpp
)

add_executable(unit-test ${SOURCES})
target_compile_definitions(unit-test
    PRIVATE
        -DNOMINMAX
        -DWIN32_LEAN_AND_MEAN
        -DVC_EXTRALEAN
        -D_CRT_SECURE_NO_WARNINGS
        -D_SECURE_SCL=0
        -D_SCL_SECURE_NO_WARNINGS
)
target_include_directories(unit-test PRIVATE ${INCLUDE_PATHS})
target_link_libraries(unit-test misc)
