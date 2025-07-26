# library paltform
# aux_source_directory(. PLATFORM_SRC)
# aux_source_directory(node PLATFORM_SRC)
# aux_source_directory(param PLATFORM_SRC)
set(PLATFORM_SRC
	node/df_node_parser.cpp
	node/node.cpp
	node/df_node.cpp
	param/param.cpp
	platform.cpp
)

add_library(platform STATIC ${PLATFORM_SRC})
target_include_directories(platform PUBLIC ${SRC_ROOT}/include/platform)

if(PLATFORM_INFO)
	target_compile_definitions(platform PRIVATE M_DEBUG)
endif()
if(PLATFORM_DEBUG)
	target_compile_definitions(platform PRIVATE M_DEBUG_VERBOSE)
endif()

target_link_libraries(platform PUBLIC util)

# test latency
# set(LATENCY_SRC
# 	latency/multi_lat.cpp
# )

# add_executable(hlop_multi_lat ${LATENCY_SRC})

# if(PLATFORM_INFO)
# 	target_compile_definitions(hlop_multi_lat PRIVATE M_DEBUG)
# endif()
# if(PLATFORM_DEBUG)
# 	target_compile_definitions(hlop_multi_lat PRIVATE M_DEBUG_VERBOSE)
# endif()

# target_link_libraries(hlop_multi_lat mpi)