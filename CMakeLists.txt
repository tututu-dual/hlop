cmake_minimum_required(VERSION 3.12)

project(H-Lop VERSION 0.1)

# compile flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# dependencies
set(DEPS_ROOT ${CMAKE_SOURCE_DIR}/deps)
include(cmake/dependencies.cmake)
setup_dependencies()

# src directory
set(SRC_ROOT ${CMAKE_SOURCE_DIR}/src)

# output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# resource file configure
if(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(RESOURCE_ROOT "${CMAKE_INSTALL_PREFIX}/share/resources/")
else()
	set(RESOURCE_ROOT "${CMAKE_SOURCE_DIR}/resources")
endif()
configure_file(
	cmake/configs/resources.h.in
	${CMAKE_BINARY_DIR}/include/resources.h
)

# compile
if(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_subdirectory(src)
	# add_subdirectory(tests)
else()
	add_subdirectory(src)
	add_subdirectory(tests)
endif()


# install
if(CMAKE_BUILD_TYPE STREQUAL "Release")
	install(DIRECTORY src/include/
		DESTINATION ${CMAKE_INSTALL_PREFIX}/include
		FILE_PERMISSIONS
			OWNER_READ OWNER_WRITE
			GROUP_READ
			WORLD_READ
	)
	install(DIRECTORY build/include/
		DESTINATION ${CMAKE_INSTALL_PREFIX}/include
		FILE_PERMISSIONS
			OWNER_READ OWNER_WRITE
			GROUP_READ
			WORLD_READ
	)
	install(DIRECTORY bin/
		DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
		FILE_PERMISSIONS
			OWNER_READ OWNER_WRITE OWNER_EXECUTE
			GROUP_READ GROUP_EXECUTE
			WORLD_READ WORLD_EXECUTE
	)
	install(DIRECTORY lib/
		DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
		FILE_PERMISSIONS
			OWNER_READ OWNER_WRITE
			GROUP_READ
			WORLD_READ
	)
	install(DIRECTORY resources/
		DESTINATION ${CMAKE_INSTALL_PREFIX}/share/resources
		FILE_PERMISSIONS
			OWNER_READ OWNER_WRITE
			GROUP_READ
			WORLD_READ
	)
	configure_file(
		"${CMAKE_SOURCE_DIR}/cmake/uninstall.cmake.in"
		"${CMAKE_BINARY_DIR}/uninstall.cmake"
		@ONLY
	)
	add_custom_target(uninstall
		COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/uninstall.cmake"
	)
endif()