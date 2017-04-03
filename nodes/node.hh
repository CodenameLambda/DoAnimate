#ifndef nodes_node_hh
#define nodes_node_hh
#include <functional>
#include <vector>
#include "../types.hh"


namespace doanimate {
    namespace nodes {
        class Node {
            public:
            bool has_ui_operations;

            Node(const bool has_ui_operations);

            virtual void update() = 0;

            virtual std::vector<types::Value>& get_inputs() = 0;

            virtual const std::vector<types::Value>& get_outputs() = 0;

            virtual const std::vector<types::TypeInfo>& get_input_type_infos() = 0;

            virtual const std::vector<std::string>& get_input_names() = 0;

            virtual const std::vector<types::TypeInfo>& get_output_type_infos() = 0;

            virtual const std::vector<std::string>& get_output_names() = 0;

            virtual void run_ui_operations();

            virtual bool has_requesting();

            virtual std::vector<size_t> requester(std::vector<bool> already_loaded);
        };

        
        class DefaultNode : public Node {
            protected:
            using imp_t = std::function<
                std::vector<types::Value>(std::vector<types::Value>)
            >;

            imp_t implementation;

            std::vector<types::TypeInfo> input_type_infos;

            std::vector<std::string> input_names;

            std::vector<types::TypeInfo> output_type_infos;

            std::vector<std::string> output_names;

            std::vector<types::Value> inputs;

            std::vector<types::Value> outputs;

            public:
            DefaultNode(
                imp_t implementation,
                const std::vector<types::TypeInfo>& input_type_infos,
                const std::vector<std::string>& input_names,
                const std::vector<types::TypeInfo>& output_type_infos,
                const std::vector<std::string>& output_names,
                const std::vector<types::Value>& default_inputs = {}
            );

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
