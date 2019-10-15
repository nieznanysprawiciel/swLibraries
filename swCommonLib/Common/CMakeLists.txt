
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${swCommonLib_SOURCE_DIR}/Common/*")
file(GLOB PCH_LIST CONFIGURE_DEPENDS "${swCommonLib_SOURCE_DIR}/Common/stdafx.*")

add_library(CommonBase STATIC ${SOURCE_LIST})

target_include_directories(CommonBase PUBLIC ${swCommonLib_SOURCE_DIR}/../)
target_compile_features(CommonBase PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/Common" PREFIX "CommonBase" FILES ${SOURCE_LIST})
source_group(TREE "${PROJECT_SOURCE_DIR}/Common" PREFIX "PrecompiledHeader" FILES ${PCH_LIST})
