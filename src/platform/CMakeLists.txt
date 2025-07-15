# library paltform
aux_source_directory(. PLATFORM_SRC)
aux_source_directory(node PLATFORM_SRC)
aux_source_directory(param PLATFORM_SRC)

add_library(platform STATIC ${PLATFORM_SRC})
target_include_directories(platform PUBLIC ${SRC_DIR}/include/platform)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(platform PRIVATE M_DEBUG)
endif()

target_link_libraries(platform PUBLIC util)