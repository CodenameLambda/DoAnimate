#include "node.hh"


namespace doanimate
{
	namespace nodes
	{
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
	}
}
