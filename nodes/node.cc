#include "node.hh"


namespace doanimate {
	namespace nodes {
		void default_node::update() {
			outputs = implementation(inputs);
		}


		std::vector<types::value>& default_node::get_inputs() {
			return inputs;
		}

		 
		const std::vector<types::value>& default_node::get_outputs() {
			return outputs;
		}


		const std::vector<types::type_info>& default_node::get_input_type_infos() {
			return input_type_infos;
		}


		const std::vector<types::type_info>& default_node::get_output_type_infos() {
			return output_type_infos;
		}
	}
}
