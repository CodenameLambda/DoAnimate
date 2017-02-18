#include "../nodes/node.hh"
#include <functional>


namespace doanimate {
	namespace shapes {
		using nptr = nodes::node*;

		nptr line();
		nptr polygon();
		nptr regular_polygon();
		nptr ellipse();
		nptr circle();
	}
}
