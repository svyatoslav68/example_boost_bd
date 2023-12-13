cmake_minimum_required(VERSION 3.2)

project("Connection with SOCI library" VERSION 0.0.1)

message("building library soci_bd")
set(TARGET_LIBSOCI soci_connection)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
message("HEADERS_DIR for library: ${HEADERS_DIR}")

set(SOURCES ${SOURCE_DIR}/connection.cpp)

list(APPEND CMAKE_MODULE_PATH $ENV{HOME}/cmake_modules)
message("CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")

add_library(${TARGET_LIBSOCI} ${SOURCES})

find_package(MySQL)
if(MYSQL_FOUND)
	message("MySql found")
	message("MYSQL_INCLUDE_DIR = ${MYSQL_INCLUDE_DIR}")
	target_include_directories(${TARGET_LIBSOCI} PRIVATE ${MYSQL_INCLUDE_DIR})
	target_link_libraries(${TARGET_LIBSOCI} ${MYSQL_LIBRARIES})
else()
	message("MySql not found")
	find_package(MariaDBClient)
	if (MariaDBClient_FOUND)
		message("MariaDBClient found")
		target_include_directories(${TARGET_LIBSOCI} PRIVATE ${MariaDBClient_INCLUDE_DIRS})
		target_link_libraries(${TARGET_LIBSOCI} ${MariaDBClient_LIBRARIES})
	else()
		message("MariaDBClient not found")
	endif()
endif()

#find_package(Soci)
#if(SOCI_FOUND)
#	target_include_directories(${TARGET_LIBSOCI} PRIVATE ${SOCI_INCLUDE_DIR})
#	target_link_libraries(${TARGET_LIBSOCI} ${SOCI_LIBRARY})
#	target_link_libraries(${TARGET_LIBSOCI} ${SOCI_mysql_PLUGIN})
#	target_link_libraries(${TARGET_LIBSOCI} ${SOCI_postgresql_PLUGIN})
#else()
#	message("Soci not found")
#endif()
#
#message("Ищем Boost")
#find_package(Boost COMPONENTS program_options)
#if (Boost_FOUND)
#	message("Найден Boost")
#	target_include_directories(${TARGET_LIBSOCI} PRIVATE ${Boost_INCLUDE_DIR})
#	target_link_libraries(${TARGET_LIBSOCI} ${Boost_LIBRARIES})
#endif()
#
target_include_directories(${TARGET_LIBSOCI} PRIVATE ${HEADERS_DIR})

set_target_properties(
	${TARGET_LIBSOCI} PROPERTIES
	CXX_STANDARD 17	#Собирать в соответствии со стандартом c++17
	)
