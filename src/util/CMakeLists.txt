# library paltform
# aux_source_directory(. UTIL_SRC)
set(UTIL_SRC
	aux.cpp
	fit.cpp
)

add_library(util STATIC ${UTIL_SRC})
target_include_directories(util PUBLIC ${SRC_ROOT}/include/util)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(util PRIVATE M_DEBUG)
endif()

target_link_libraries(util PUBLIC magic_enum PRIVATE GSL::gsl PRIVATE GSL::gslcblas)