# library paltform
# aux_source_directory(. PLATFORM_SRC)
# aux_source_directory(node PLATFORM_SRC)
# aux_source_directory(param PLATFORM_SRC)
set(PLATFORM_SRC
	node/df_node_parser.cpp
	param/param.cpp
	platform.cpp
)

add_library(platform STATIC ${PLATFORM_SRC})
target_include_directories(platform PUBLIC ${SRC_ROOT}/include/platform)

if(PLATFORM_DEBUG)
	target_compile_definitions(platform PRIVATE M_DEBUG)
endif()

target_link_libraries(platform PUBLIC util)