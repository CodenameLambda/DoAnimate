#ifndef nodes_node_h
#define nodes_node_h
#include <functional>
#include <vector>
#include "../types.hh"


namespace doanimate {
	namespace nodes {
		class node {
			public:
				const bool has_ui_operations;

				node(const bool has_ui_operations) : has_ui_operations(has_ui_operations) {
				}

				virtual void update() = 0;
				virtual std::vector<types::value>& get_inputs() = 0;
				virtual const std::vector<types::value>& get_outputs() = 0;
				virtual const std::vector<types::type_info>& get_input_type_infos() = 0;
				virtual const std::vector<std::string>& get_input_names() = 0;
				virtual const std::vector<types::type_info>& get_output_type_infos() = 0;
				virtual const std::vector<std::string>& get_output_names() = 0;
				virtual void run_ui_operations() {
				}
		};

		
		class default_node : public node {
			protected:
				std::function<std::vector<types::value>(std::vector<types::value>)> implementation;
				const std::vector<types::type_info> input_type_infos;
				const std::vector<std::string> input_names;
				const std::vector<types::type_info> output_type_infos;
				const std::vector<std::string> output_names;
				std::vector<types::value> inputs;
				std::vector<types::value> outputs;

			public:
				default_node(decltype(implementation) implementation, decltype(input_type_infos) input_type_infos,
						decltype(input_names) input_names, decltype(output_type_infos) output_type_infos,
						decltype(output_names) output_names, decltype(inputs) default_inputs)
				: node(false), implementation(implementation), input_type_infos(input_type_infos), 
				  input_names(input_names), output_type_infos(output_type_infos), output_names(output_names), inputs(default_inputs) {
				}

				default_node(decltype(implementation) implementation, decltype(input_type_infos) input_type_infos,
						decltype(input_names) input_names, decltype(output_type_infos) output_type_infos,
						decltype(output_names) output_names)
				: default_node(implementation, input_type_infos, input_names, output_type_infos, output_names,
						decltype(inputs)(input_type_infos.size(), false)) {
				}

				virtual void update();
				virtual std::vector<types::value>& get_inputs();
				virtual const std::vector<types::value>& get_outputs();
				virtual const std::vector<types::type_info>& get_input_type_infos();
				virtual const std::vector<std::string>& get_input_names();
				virtual const std::vector<types::type_info>& get_output_type_infos();
				virtual const std::vector<std::string>& get_output_names();
		};
	}
}
#endif
