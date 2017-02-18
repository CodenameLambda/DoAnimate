cmake_minimum_required (VERSION 2.6)

# add_definitions (-std=c++1z -O3 -Os)
add_definitions (-std=c++11 -O0 -g)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

project (DoAnimate)

find_package (Boost COMPONENTS system REQUIRED)

set (CMAKE_USE_RELATIVE_PATHS TRUE)

add_subdirectory (nodes)
add_subdirectory (shapes)
add_subdirectory (helpers)

set (DoAnimate_VERSION_MAJOR 1)
set (DoAnimate_VERSION_MINOR 0)

add_executable (DoAnimate main.cc types.hh types.cc)
target_link_libraries (DoAnimate nodes shapes helpers)

link_directories (${Boost_LIBRARY_DIRS})

if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(DoAnimate ${Boost_SYSTEM_LIBRARY})
endif()

install (TARGETS DoAnimate DESTINATION bin)
