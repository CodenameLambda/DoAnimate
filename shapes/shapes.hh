#ifndef shapes_shapes_hh
#define shapes_shapes_hh
#include "../nodes/node.hh"
#include <functional>


namespace doanimate
{
	namespace shapes
	{
		nodes::Node* line();


		nodes::Node* polygon();


		nodes::Node* regular_polygon();


		nodes::Node* ellipse();


		nodes::Node* circle();
	}
}
#endif
