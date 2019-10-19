cmake_minimum_required(VERSION 3.15)

project(swCommonLib
        VERSION 0.52.0
        DESCRIPTION "Common functionalities for Sleeping Wombat Libraries"
        LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

add_subdirectory(Common)
#add_subdirectory(External)
add_subdirectory(HierarchicalChunkedFormat)
#add_subdirectory(ParameterAnimation)
#add_subdirectory(Reflection)
#add_subdirectory(Serialization)
#add_subdirectory(System)
#add_subdirectory(TestUtils)


# Import rttr reflection library
add_subdirectory(Reflection)

find_package(RTTR CONFIG REQUIRED Core)
add_library(RTTR INTERFACE IMPORTED)

set_property(TARGET RTTR PROPERTY BUILD_BENCHMARKS False)



if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(Tests)
endif()

# Disable creating ZERO_CHECK project
set(CMAKE_SUPPRESS_REGENERATION true)
