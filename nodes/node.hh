#ifndef Nodes_Node_h
#define Nodes_Node_h
#include <functional>
#include <vector>
#include "../types.hh"


namespace doanimate {
	namespace nodes {
		class Node {
			public:
				const bool has_ui_operations;

				Node(const bool has_ui_operations)
					: has_ui_operations(has_ui_operations) {
				}

				virtual void update() = 0;
				virtual std::vector<types::Value>& get_inputs() = 0;
				virtual const std::vector<types::Value>& get_outputs() = 0;
				virtual const std::vector<types::TypeInfo>& get_input_type_infos() = 0;
				virtual const std::vector<std::string>& get_input_names() = 0;
				virtual const std::vector<types::TypeInfo>& get_output_type_infos() = 0;
				virtual const std::vector<std::string>& get_output_names() = 0;
				virtual void run_ui_operations() {
				}
		};

		
		class DefaultNode : public Node {
			protected:
				using imp_t = std::function<
					std::vector<types::Value>(std::vector<types::Value>)
				>;
				imp_t implementation;
				const std::vector<types::TypeInfo> input_type_infos;
				const std::vector<std::string> input_names;
				const std::vector<types::TypeInfo> output_type_infos;
				const std::vector<std::string> output_names;
				std::vector<types::Value> inputs;
				std::vector<types::Value> outputs;

			public:
				DefaultNode(imp_t implementation,
						decltype(input_type_infos) input_type_infos,
						decltype(input_names) input_names,
						decltype(output_type_infos) output_type_infos,
						decltype(output_names) output_names,
						decltype(inputs) default_inputs)
				: Node(false), implementation(implementation),
				  input_type_infos(input_type_infos), input_names(input_names),
				  output_type_infos(output_type_infos), output_names(output_names),
				  inputs(default_inputs) {
				}

				DefaultNode(decltype(implementation) implementation,
						decltype(input_type_infos) input_type_infos,
						decltype(input_names) input_names,
						decltype(output_type_infos) output_type_infos,
						decltype(output_names) output_names)
				: DefaultNode(implementation, input_type_infos, input_names,
						output_type_infos, output_names,
						decltype(inputs)(input_type_infos.size(), false)) {
				}

				virtual void update();
				virtual std::vector<types::Value>& get_inputs();
				virtual const std::vector<types::Value>& get_outputs();
				virtual const std::vector<types::TypeInfo>& get_input_type_infos();
				virtual const std::vector<std::string>& get_input_names();
				virtual const std::vector<types::TypeInfo>& get_output_type_infos();
				virtual const std::vector<std::string>& get_output_names();
		};
	}
}
#endif
