

file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${swCommonLib_SOURCE_DIR}/HierarchicalChunkedFormat/*")
file(GLOB PCH_LIST CONFIGURE_DEPENDS "${swCommonLib_SOURCE_DIR}/HierarchicalChunkedFormat/stdafx.*")

add_library(HCF STATIC ${SOURCE_LIST} )

target_include_directories(HCF PUBLIC ${swCommonLib_SOURCE_DIR}/../)
target_compile_features(HCF PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/HierarchicalChunkedFormat" PREFIX "HCF" FILES ${SOURCE_LIST})
source_group(TREE "${PROJECT_SOURCE_DIR}/HierarchicalChunkedFormat" PREFIX "PrecompiledHeader" FILES ${PCH_LIST})

