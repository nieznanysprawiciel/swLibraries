## ParameterAnimation cmake file

message("Configuring ParameterAnimation library")

file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${swCommonLib_SOURCE_DIR}/ParameterAnimation/*")

add_library(ParameterAnimation STATIC ${SOURCE_LIST})
target_include_directories(ParameterAnimation
    PUBLIC 
        $<BUILD_INTERFACE:${swCommonLib_SOURCE_DIR}/../>
        $<INSTALL_INTERFACE:${swCommonLib_SOURCE_DIR}/../>
)
target_link_libraries(ParameterAnimation PUBLIC CommonBase)