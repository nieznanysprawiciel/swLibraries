## TestHelpers cmake file

set(TEST_NAME "TestHelpers")
set(SOURCE_DIR "${swCommonLib_SOURCE_DIR}/Tests/${TEST_NAME}/")

message("Configuring ${TEST_NAME} test")

file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${SOURCE_DIR}/*")

add_executable(${TEST_NAME} "${SOURCE_LIST}")
target_link_libraries(${TEST_NAME} PUBLIC CommonBase)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

source_group(TREE "${SOURCE_DIR}" PREFIX "${TEST_NAME}" FILES ${SOURCE_LIST})
