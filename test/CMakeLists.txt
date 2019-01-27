cmake_minimum_required (VERSION 3.4)

include(GoogleTest)

macro(${PROJECT_NAME}_discover_tests TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} ${PROJECT_NAME} gtest gtest_main)
    gtest_discover_tests(${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
    target_compile_features(${TESTNAME} PUBLIC cxx_std_17)
    set_target_properties(${TESTNAME} PROPERTIES CXX_EXTENSIONS OFF)
endmacro()

add_definitions(
    -DNOMINMAX
    -DWIN32_LEAN_AND_MEAN
    -DVC_EXTRALEAN
    -D_CRT_SECURE_NO_WARNINGS
    -D_SECURE_SCL=0
    -D_SCL_SECURE_NO_WARNINGS
)
include_directories(googletest/googletest/include)

file(GLOB FILES *.cpp)
foreach(FILE ${FILES})
    get_filename_component(TEST ${FILE} NAME_WE)
    Misc_discover_tests(${TEST} ${FILE})
endforeach()

add_subdirectory(googletest)
