#include "types.hh"
#include <map>


namespace doanimate {
	namespace types {
		namespace implementation {
			const type_info type_info::boolean = type_info_enum::boolean;
			const type_info type_info::integer = type_info_enum::integer;
			const type_info type_info::number = type_info_enum::number;
			const type_info type_info::any = type_info_enum::any;
			const type_info type_info::string = type_info_enum::string;
			const type_info type_info::none = type_info::tuple({});
			const type_info type_info::position = type_info::tuple(type_info::number, 2)
				.labeled("position");
			const type_info type_info::position2d = type_info::position;
			const type_info type_info::position3d = type_info::tuple(type_info::number, 3)
				.labeled("position3d");
			const type_info type_info::color = type_info::tuple(type_info::number, 4)
				.labeled("color");
			const type_info type_info::color_without_alpha = type_info::position3d
				.labeled("color_without_alpha");
			const type_info type_info::renderable = type_info::function(
					type_info::color,
					{type_info::position2d}
				).labeled("renderable");
			const type_info type_info::sound = type_info::function(
					type_info::number,
					{type_info::number}
				).labeled("sound");
		}

		type_info simplify(const type_info t) {
			return apply_specialization(t, {});
		}

		type_info apply_specialization(const type_info t, const std::vector<type_info> args) {
			if (t.is_code()) {
				auto ins = t.code_inputs();
				auto outs = t.code_outputs();
				for (auto& i : ins)
					i = apply_specialization(i, args);
				for (auto& i : outs)
					i = apply_specialization(i, args);
				return type_info::code(ins, outs);
			}
			else if (t.is_list())
				return type_info::list(apply_specialization(t.list_of(), args));
			else if (t.is_tuple()) {
				auto ts = t.tuple_types();
				for (auto& i : ts)
					i = apply_specialization(i, args);
				return type_info::tuple(ts);
			}
			else if (t.is_function()) {
				auto args2 = t.function_arguments();
				for (auto& i : args2)
					i = apply_specialization(i, args);
				return type_info::function(apply_specialization(t.function_return_type(), args), args2);
			}
			else if (t.is_specialization())
				return apply_specialization(t.specialization_template(), t.specialization_parameters());
			else if (t.is_generic_parameter())
				return args[t.generic_parameter_index()];
			else
				return t;
		}

		std::string to_string(const std::vector<type_info> ts) {
			bool first = true;
			std::string out = "[";
			for (const auto& i : ts) {
				out += to_string(i);
				if (first)
					first = false;
				else
					out += ", ";
			}
			return out + "]";
		}

		const std::map<type_info, std::string> names {
			{type_info::boolean, "boolean"},
				{type_info::integer, "integer"},
				{type_info::number, "number"},
				{type_info::string, "string"},
				{type_info::any, "any"}
		};

		std::string to_string(const type_info t) {
			if (t.has_label())
				return t.label();
			else if (t.is_code())
				return "code[" + to_string(t.code_inputs()) + ", " + to_string(t.code_outputs()) + "]";
			else if (t.is_list())
				return "list[" + to_string(t.list_of()) + "]";
			else if (t.is_repeated_tuple())
				return "tuple[" + to_string(t.repeated_tuple_of()) + ", " + std::to_string(t.repeated_tuple_length()) + "]";
			else if (t.is_tuple())
				return "tuple" + to_string(t.tuple_types());
			else if (t.is_function())
				return "function[" + to_string(t.function_return_type()) + ", " + to_string(t.function_arguments()) + "]";
			else if (t.is_specialization())
				return "specialize[" + to_string(t.specialization_template()) + ", " + to_string(t.specialization_parameters()) + "]";
			else if (t.is_generic_parameter())
				return "template_parameter[" + std::to_string(t.generic_parameter_index()) + "]";
			else
				return (*names.find(t)).second;
		}
	}
}
