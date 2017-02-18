#include "shapes.hh"


namespace doanimate {
	namespace shapes {
		nptr line() {
			return new nodes::default_node(
					[](std::vector<types::value>) -> std::vector<types::value> {
						return {};
					},
					{types::type_info
			);
		}
	}
}
