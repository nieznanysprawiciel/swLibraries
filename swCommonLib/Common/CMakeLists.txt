## CommonBase cmake file

file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${swCommonLib_SOURCE_DIR}/Common/*")
#file(GLOB_RECURSE SYSTEM_SOURCE_LIST CONFIGURE_DEPENDS "${swCommonLib_SOURCE_DIR}/System/*")
file(GLOB PCH_LIST CONFIGURE_DEPENDS "${swCommonLib_SOURCE_DIR}/Common/stdafx.*")

add_library(CommonBase STATIC ${SOURCE_LIST})
#add_library(CommonBase STATIC ${SOURCE_LIST}${SYSTEM_SOURCE_LIST})

target_include_directories(CommonBase PUBLIC ${swCommonLib_SOURCE_DIR}/../)
target_compile_features(CommonBase PUBLIC cxx_std_11)

target_link_libraries(CommonBase RTTR::Core)

source_group(TREE "${PROJECT_SOURCE_DIR}/Common" PREFIX "CommonBase" FILES ${SOURCE_LIST})
#source_group(TREE "${PROJECT_SOURCE_DIR}/System" PREFIX "System" FILES ${SYSTEM_SOURCE_LIST})
source_group(TREE "${PROJECT_SOURCE_DIR}/Common" PREFIX "PrecompiledHeader" FILES ${PCH_LIST})