# executable cli program
# aux_source_directory(. MAIN_SRC)
set(MAIN_SRC
	main.cpp
)

add_executable(hlop ${MAIN_SRC})
target_include_directories(hlop PRIVATE ${SRC_ROOT}/include/main)

if(MAIN_INFO)
	target_compile_definitions(hlop PRIVATE M_DEBUG)
endif()
if(MAIN_DEBUG)
	target_compile_definitions(hlop PRIVATE M_DEBUG_VERBOSE)
endif()

target_link_libraries(hlop PRIVATE coll PRIVATE gflags)