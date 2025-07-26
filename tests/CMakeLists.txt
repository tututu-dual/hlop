cmake_minimum_required(VERSION 3.10)

add_definitions(-DM_DEBUG)

# test util
set(UTIL_TEST_SRC test_util.cpp)
add_executable(test_util ${UTIL_TEST_SRC})
target_link_libraries(test_util util)

#test param
set(PARAM_TEST_SRC test_param.cpp)
add_executable(test_param ${PARAM_TEST_SRC})
target_link_libraries(test_param platform)

#test node parser
set(PARSER_TEST_SRC test_node_parser.cpp)
add_executable(test_parser ${PARSER_TEST_SRC})
target_link_libraries(test_parser platform)

# test types
set(TYPE_TEST_SRC test_type.cpp)
add_executable(test_type ${TYPE_TEST_SRC})
target_link_libraries(test_type coll)

# test comm_pair
set(COMM_PAIR_TEST_SRC test_comm_pair.cpp)
add_executable(test_comm_pair ${COMM_PAIR_TEST_SRC})
target_link_libraries(test_comm_pair coll)

# test node_list
set(NODE_LIST_TEST_SRC test_node_list.cpp)
add_executable(test_node_list ${NODE_LIST_TEST_SRC})
target_link_libraries(test_node_list coll)

# test allgather
set(ALLGATHER_TEST_SRC test_allgather.cpp)
add_executable(test_allgather ${ALLGATHER_TEST_SRC})
target_link_libraries(test_allgather coll)

# test bcast
set(BCAST_TEST_SRC test_bcast.cpp)
add_executable(test_bcast ${BCAST_TEST_SRC})
target_link_libraries(test_bcast coll)

# test scatter
set(SCATTER_TEST_SRC test_scatter.cpp)
add_executable(test_scatter ${SCATTER_TEST_SRC})
target_link_libraries(test_scatter coll)