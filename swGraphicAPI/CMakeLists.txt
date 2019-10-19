cmake_minimum_required(VERSION 3.15)

project(swGraphicAPI
        VERSION 0.54.1
        DESCRIPTION "Graphic libraries and resources managment"
        LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

add_subdirectory(Assets)
add_subdirectory(DX11API)
add_subdirectory(ImageGenerators)
add_subdirectory(Loaders)
add_subdirectory(MockAPI)
add_subdirectory(MockAssets)
add_subdirectory(OpenGL)
add_subdirectory(Rendering)
add_subdirectory(ResourceManager)
add_subdirectory(Resources)

f((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(Tests)
endif()

