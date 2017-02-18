add_library (helpers ranges.hh ranges.cc variadic.hh)

link_directories (${Boost_LIBRARY_DIRS})

if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(helpers ${Boost_SYSTEM_LIBRARY})
endif()

install (TARGETS helpers DESTINATION bin)
