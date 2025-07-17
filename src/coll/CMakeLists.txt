# library coll
# aux_source_directory(. COLL_SRC)
# aux_source_directory(struct COLL_SRC)
set(COLL_SRC
	struct/comm_pair.cpp
	struct/node_list.cpp
	struct/type.cpp
	allgather.cpp
	allreduce.cpp
	alltoall.cpp
	bcast.cpp
	collective.cpp
	gather.cpp
	reduce.cpp
	scatter.cpp
)

add_library(coll STATIC ${COLL_SRC})
target_include_directories(coll
	PUBLIC ${SRC_ROOT}/include/coll
	PUBLIC ${CMAKE_BINARY_DIR}/include
)

if(COLL_INFO)
	target_compile_definitions(coll PRIVATE M_DEBUG)
endif()
if(COLL_DEBUG)
	target_compile_definitions(coll PRIVATE M_DEBUG_VERBOSE)
endif()

target_link_libraries(coll PUBLIC platform)