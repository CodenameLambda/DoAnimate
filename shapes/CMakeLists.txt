add_library (shapes shapes.hh shapes.cc)

link_directories (${Boost_LIBRARY_DIRS})

if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(shapes ${Boost_SYSTEM_LIBRARY})
endif()

install (TARGETS shapes DESTINATION bin)
