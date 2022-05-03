cmake_minimum_required(VERSION 3.10)

project(program_options)

set(TARGET prog_opts)

list(APPEND CMAKE_MODULE_PATH $ENV{HOME}/cmake_modules)

#message("Source directory: ${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers)

set(SOURCES ${SRC_DIR}/main.cpp ${SRC_DIR}/cli_options.cpp)
add_executable(${TARGET} ${SOURCES})

target_include_directories(${TARGET} PRIVATE ${HEADERS_DIR})
find_package(Boost COMPONENTS program_options)
if(Boost_FOUND)
	message("Ok boost")
	target_link_libraries(${TARGET} ${Boost_LIBRARIES})
	target_include_directories(${TARGET} PRIVATE ${Boost_INCLUDE_DIRS})
	#target_link_libraries(${TARGET} ${Boost_LIBRARIES})
endif()

find_package(Soci)
if(SOCI_FOUND)
	target_include_directories(${TARGET} PRIVATE ${SOCI_INCLUDE_DIR})
	target_link_libraries(${TARGET} ${SOCI_LIBRARY})
	target_link_libraries(${TARGET} ${SOCI_mysql_PLUGIN})
	target_link_libraries(${TARGET} ${SOCI_postgresql_PLUGIN})
else()
	message("Soci not found")
endif()

target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/soci_bd/include)

add_subdirectory(soci_bd ${CMAKE_CURRENT_SOURCE_DIR}/soci_bd/lib)
target_link_libraries(${TARGET} ${CMAKE_CURRENT_SOURCE_DIR}/soci_bd/lib/libsoci_connection.a)

set_target_properties(
	${TARGET} PROPERTIES
	CXX_STANDARD 17
	)
