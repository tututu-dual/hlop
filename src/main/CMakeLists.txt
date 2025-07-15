# executable cli program
# aux_source_directory(. MAIN_SRC)
set(MAIN_SRC
	main.cpp
)

add_executable(main ${MAIN_SRC})
target_include_directories(main PRIVATE ${SRC_DIR}/include/main)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(main PRIVATE M_DEBUG)
endif()

target_link_libraries(main PRIVATE gflags PRIVATE coll)