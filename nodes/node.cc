#include "node.hh"


namespace doanimate
{
	namespace nodes
	{
		Node::Node(const bool has_ui_operations)
		{
			this->has_ui_operations = has_ui_operations;
		}

		void Node::run_ui_operations()
		{}

		bool Node::has_requesting()
		{
			return false;
		}

		void DefaultNode::update()
		{
			outputs = implementation(inputs);
		}


		std::vector<types::Value>& DefaultNode::get_inputs()
		{
			return inputs;
		}

		 
		const std::vector<types::Value>& DefaultNode::get_outputs()
		{
			return outputs;
		}


		const std::vector<types::TypeInfo>& DefaultNode::get_input_type_infos()
		{
			return input_type_infos;
		}


		const std::vector<types::TypeInfo>& DefaultNode::get_output_type_infos()
		{
			return output_type_infos;
		}

		std::vector<size_t> Node::requester(std::vector<bool>)
		{
			return {};
		}

		DefaultNode::DefaultNode(
			DefaultNode::imp_t implementation,
			const std::vector<types::TypeInfo>& input_type_infos,
			const std::vector<std::string>& input_names,
			const std::vector<types::TypeInfo>& output_type_infos,
			const std::vector<std::string>& output_names,
			const std::vector<types::Value>& default_inputs
		) : Node(false)
		{
			this->implementation = implementation;
			this->input_type_infos = input_type_infos;
			this->input_names = input_names;
			this->output_type_infos = output_type_infos;
			this->output_names = output_names;
			this->inputs = default_inputs;
			if (this->inputs.size() == 0)
				this->outputs = std::vector<types::Value>(input_type_infos.size());
			this->outputs = std::vector<types::Value>(input_type_infos.size());
		}
	}
}
