add_library (nodes node.hh node.cc node_system.hh node_system.cc)

link_directories (${Boost_LIBRARY_DIRS})

if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(nodes ${Boost_SYSTEM_LIBRARY})
endif()

install (TARGETS nodes DESTINATION bin)
