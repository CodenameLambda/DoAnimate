#include "types.hh"
#include <unordered_map>


namespace doanimate
{
	namespace types
	{
		namespace implementation
		{
			const TypeInfo TypeInfo::boolean = TypeInfoEnum::boolean;

			const TypeInfo TypeInfo::integer = TypeInfoEnum::integer;

			const TypeInfo TypeInfo::number = TypeInfoEnum::number;

			const TypeInfo TypeInfo::any = TypeInfoEnum::any;

			const TypeInfo TypeInfo::string = TypeInfoEnum::string;

			const TypeInfo TypeInfo::none = TypeInfo::tuple({});

			const TypeInfo TypeInfo::position = TypeInfo::tuple(
				TypeInfo::number,
				2
			).labeled("position");

			const TypeInfo TypeInfo::position2d = TypeInfo::position;

			const TypeInfo TypeInfo::position3d = TypeInfo::tuple(
				TypeInfo::number,
				3
			).labeled("position3d");

			const TypeInfo TypeInfo::color = TypeInfo::tuple(
				TypeInfo::number,
				4
			).labeled("color");

			const TypeInfo TypeInfo::color_without_alpha = TypeInfo::position3d.labeled(
				"color_without_alpha"
			);

			const TypeInfo TypeInfo::renderable = TypeInfo::function(
				TypeInfo::color,
				{TypeInfo::position2d}
			).labeled("renderable");

			const TypeInfo TypeInfo::sound = TypeInfo::function(
				TypeInfo::number,
				{TypeInfo::number}
			).labeled("sound");
		}


		TypeInfo simplify(const TypeInfo t)
		{
			return apply_specialization(t, {});
		}


		TypeInfo apply_specialization(
			const TypeInfo t,
			const std::vector<TypeInfo> args
		)
		{
			if (t.is_code())
			{
				auto ins = t.code_inputs();
				auto outs = t.code_outputs();

				for (auto& i : ins)
					i = apply_specialization(i, args);

				for (auto& i : outs)
					i = apply_specialization(i, args);

				return TypeInfo::code(ins, outs);
			}
			else if (t.is_list())
				return TypeInfo::list(apply_specialization(t.list_of(), args));
			else if (t.is_tuple())
			{
				auto ts = t.tuple_types();

				for (auto& i : ts)
					i = apply_specialization(i, args);

				return TypeInfo::tuple(ts);
			}
			else if (t.is_function())
			{
				auto args2 = t.function_arguments();

				for (auto& i : args2)
					i = apply_specialization(i, args);

				return TypeInfo::function(apply_specialization(t.function_return_type(), args), args2);
			}
			else if (t.is_specialization())
				return apply_specialization(t.specialization_template(), t.specialization_parameters());
			else if (t.is_generic_parameter())
				return args[t.generic_parameter_index()];
			else
				return t;
		}


		std::string to_string(const std::vector<TypeInfo> ts)
		{
			bool first = true;
			std::string out = "[";

			for (const auto& i : ts)
			{
				out += to_string(i);

				if (first)
					first = false;
				else
					out += ", ";
			}
			return out + "]";
		}


		const std::unordered_map<TypeInfo, std::string> names {
			{TypeInfo::boolean, "boolean"},
			{TypeInfo::integer, "integer"},
			{TypeInfo::number, "number"},
			{TypeInfo::string, "string"},
			{TypeInfo::any, "any"}
		};


		std::string to_string(const TypeInfo t)
		{
			if (t.has_label())
				return t.label();
			else if (t.is_code())
				return "code[" + to_string(t.code_inputs()) + ", " +
					to_string(t.code_outputs()) + "]";
			else if (t.is_list())
				return "list[" + to_string(t.list_of()) + "]";
			else if (t.is_repeated_tuple())
				return "tuple[" + to_string(t.repeated_tuple_of()) + ", " +
					std::to_string(t.repeated_tuple_length()) + "]";
			else if (t.is_tuple())
				return "tuple" + to_string(t.tuple_types());
			else if (t.is_function())
				return "function[" + to_string(t.function_return_type()) + ", " +
					to_string(t.function_arguments()) + "]";
			else if (t.is_specialization())
				return "specialize[" + to_string(t.specialization_template()) + ", " +
					to_string(t.specialization_parameters()) + "]";
			else if (t.is_generic_parameter())
				return "template_parameter[" +
					std::to_string(t.generic_parameter_index()) + "]";
			else
				return names.find(t)->second;
		}
	}
}


size_t combine_hashes(std::vector<size_t> hashes)
{
	size_t out = 0;

	for (const auto& i : hashes)
		out ^= i;

	return out;
}


using TypeInfo = doanimate::types::TypeInfo;


const std::unordered_map<TypeInfo, size_t> hashes {
	{TypeInfo::boolean, 1},
	{TypeInfo::integer, 3},
	{TypeInfo::number, 5},
	{TypeInfo::string, 7},
	{TypeInfo::any, 9}
};


namespace std
{
	size_t hash<TypeInfo>::operator()(const TypeInfo& t) const
	{
		auto it = hashes.find(t);

		if (it == hashes.end())
		{
			std::vector<size_t> out {
				size_t(t.category),
				(t.single_extension == nullptr)? 0 : operator()(*t.single_extension),
				t.generic_index
			};

			out.resize(out.size() + t.first_group.size() + t.second_group.size());
			size_t index = 2;

			for (const auto& i : t.first_group)
				out[++index] = operator()(i);

			for (const auto& i : t.second_group)
				out[++index] = operator()(i);

			return combine_hashes(out);
		}
		else
			return it->second;
	}
}
