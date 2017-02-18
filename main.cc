#include <iostream>
#include "nodes/node.hh"
#include "nodes/node_system.hh"

using namespace doanimate;

size_t add(nodes::node_system& ns) {
	return ns.add(new nodes::default_node(
					[](std::vector<types::value> l) -> std::vector<types::value> {
						return {boost::get<long int>(l[0]) + boost::get<long int>(l[1]), l[0]};
					},
					{types::type_info::integer, types::type_info::integer},
					{types::type_info::integer, types::type_info::integer},
					{(long int)(0), (long int)(0)}
		));
}

int main() {
	nodes::node_system ns;

	size_t first = add(ns);
	size_t second = add(ns);

	ns.at(first).n->get_inputs() = {(long int)(1), (long int)(1)};

	ns.create_connection(second, 0, {(long int)(first), (long int)(0)});
	ns.create_connection(second, 1, {(long int)(first), (long int)(1)});

	ns.rerun();

	std::cout << boost::get<long int>(ns.at(1).n->get_outputs()[0]) << " " << boost::get<long int>(ns.at(1).n->get_outputs()[1]) << std::endl;
	std::cout << "3 2" << std::endl;
}
