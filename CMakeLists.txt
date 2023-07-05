cmake_minimum_required(VERSION 3.25)
project(butterfly_counting)
set(CMAKE_CXX_STANDARD 17)

# the default build type is debug
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# if we are compiling for debug add the debug flags
if(CMAKE_BUILD_TYPE MATCHES Debug)
    # this is to make the standard lib object readable in the debugger, this will require a boost library compiled for that
    # you can provide it with -DUSE_CUSTOM_BOOST=ON and -DCUSTOM_BOOST_LOCATION=/path/to/boost
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_BUFFER_MANAGER -g")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -rdynamic -ldl" )
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -rdynamic -ldl")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -rdynamic -ldl")
    # if we are compiling for release
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    # do -O3 and set the instruction set to the native one for this machine
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -rdynamic -ldl" )
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -rdynamic -ldl")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -rdynamic -ldl")
endif ()

# 'Google_test' is the subproject name
# project(Google_tests)

# 'lib' is the folder with Google Test sources
# add_subdirectory(lib)
#  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(header/)
file(GLOB BIGRAPH_SOURCE "source/Bigraph.cpp" "source/hash.cpp" "source/countingAlgorithm.cpp")
add_library(BIGRAPH_OBJECT OBJECT ${BIGRAPH_SOURCE})
add_executable(graph_generator source/Bigraph_generator.cpp source)
add_executable(butterfly_counting main.cpp)
target_link_libraries(butterfly_counting BIGRAPH_OBJECT)
target_link_libraries(graph_generator BIGRAPH_OBJECT)

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
# add_executable(Google_Tests_run test1.cpp tests2.cpp)
# target_link_libraries(Google_Tests_run gtest gtest_main)