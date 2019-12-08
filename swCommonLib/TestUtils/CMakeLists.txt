## TestUtils cmake file
message("Configuring TestClassHierarchy library")

set(CATCH_UTILS_DIR "${swCommonLib_SOURCE_DIR}/TestUtils/CatchUtils/")
set(ANIMALS_DIR "${swCommonLib_SOURCE_DIR}/TestUtils/TestClassHierarchy/Animals/")
set(SERIALIZATION_PRIMITIVES_DIR "${swCommonLib_SOURCE_DIR}/TestUtils/TestClassHierarchy/SerializationPrimitives/")

file(GLOB_RECURSE SOURCE_LIST_CATCH_UTILS CONFIGURE_DEPENDS "${CATCH_UTILS_DIR}/*")
file(GLOB_RECURSE SOURCE_LIST_ANIMALS CONFIGURE_DEPENDS "${ANIMALS_DIR}/*")
file(GLOB_RECURSE SOURCE_LIST_SERIALIZATION_PRIMITEVES CONFIGURE_DEPENDS "${SERIALIZATION_PRIMITIVES_DIR}/*")

add_library(TestClassHierarchy STATIC ${SOURCE_LIST_CATCH_UTILS} ${SOURCE_LIST_ANIMALS} ${SOURCE_LIST_SERIALIZATION_PRIMITEVES})
target_include_directories(TestClassHierarchy
    PUBLIC 
        $<BUILD_INTERFACE:${swCommonLib_SOURCE_DIR}/../>
        $<INSTALL_INTERFACE:${swCommonLib_SOURCE_DIR}/../>
)
target_link_libraries(TestClassHierarchy PUBLIC CommonBase)

source_group(TREE "${CATCH_UTILS_DIR}" PREFIX "CatchUtils" FILES ${SOURCE_LIST_CATCH_UTILS})
source_group(TREE "${ANIMALS_DIR}" PREFIX "Animals" FILES ${SOURCE_LIST_ANIMALS})
source_group(TREE "${SERIALIZATION_PRIMITIVES_DIR}" PREFIX "SerializationPrimitives" FILES ${SOURCE_LIST_SERIALIZATION_PRIMITEVES})
