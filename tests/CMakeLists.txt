cmake_minimum_required(VERSION 3.10)

add_definitions(-DM_DEBUG)

# test util
file(GLOB UTIL_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test_util.cpp)
add_executable(test_util ${UTIL_TEST_SRC})
target_link_libraries(test_util util)

#test node parser
file(GLOB PARSER_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test_node_parser.cpp)
add_executable(test_parser ${PARSER_TEST_SRC})
target_link_libraries(test_parser platform)

#test param
file(GLOB PARAM_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test_param.cpp)
add_executable(test_param ${PARAM_TEST_SRC})
target_link_libraries(test_param platform)

# test node_list
file(GLOB NODE_LIST_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test_node_list.cpp)
add_executable(test_node_list ${NODE_LIST_TEST_SRC})
target_link_libraries(test_node_list coll)

# test commpair
file(GLOB COMM_PAIR_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test_comm_pair.cpp)
add_executable(test_comm_pair ${COMM_PAIR_TEST_SRC})
target_link_libraries(test_comm_pair coll)

# test types
file(GLOB TYPES_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test_types.cpp)
add_executable(test_types ${TYPES_TEST_SRC})
target_link_libraries(test_types coll)

# test bcast
file(GLOB BCAST_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test_bcast.cpp)
add_executable(test_bcast ${BCAST_TEST_SRC})
target_link_libraries(test_bcast coll)