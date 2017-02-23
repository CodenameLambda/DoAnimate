#define types_cc
#include "types.hh"
#include <unordered_map>


namespace doanimate
{
	namespace types
	{
		namespace implementation
		{
			TypeInfo::TypeInfo(const TypeInfoEnum cat)
			{
				category = cat;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				const TypeInfo& ext
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				TypeInfo&& ext
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				const std::vector<TypeInfo>& group
			)
			{
				category = cat;
				first_group = group;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				std::vector<TypeInfo>&& group
			)
			{
				category = cat;
				first_group = group;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				const TypeInfo& ext,
				const std::vector<TypeInfo>& group
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = group;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				TypeInfo&& ext,
				const std::vector<TypeInfo>& group
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = group;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				const TypeInfo& ext,
				std::vector<TypeInfo>&& group
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = group;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				TypeInfo&& ext,
				std::vector<TypeInfo>&& group
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = group;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				const std::vector<TypeInfo>& first,
				const std::vector<TypeInfo>& second
			)
			{
				category = cat;
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				std::vector<TypeInfo>&& first,
				const std::vector<TypeInfo>& second
			)
			{
				category = cat;
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				const std::vector<TypeInfo>& first,
				std::vector<TypeInfo>&& second
			)
			{
				category = cat;
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				std::vector<TypeInfo>&& first,
				std::vector<TypeInfo>&& second
			)
			{
				category = cat;
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				const TypeInfo& ext,
				const std::vector<TypeInfo>& first,
				const std::vector<TypeInfo>& second
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				TypeInfo&& ext,
				const std::vector<TypeInfo>& first,
				const std::vector<TypeInfo>& second
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				const TypeInfo& ext,
				std::vector<TypeInfo>&& first,
				const std::vector<TypeInfo>& second
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				TypeInfo&& ext,
				std::vector<TypeInfo>&& first,
				const std::vector<TypeInfo>& second
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				const TypeInfo& ext,
				const std::vector<TypeInfo>& first,
				std::vector<TypeInfo>&& second
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				TypeInfo&& ext,
				const std::vector<TypeInfo>& first,
				std::vector<TypeInfo>&& second
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				const TypeInfo& ext,
				std::vector<TypeInfo>&& first,
				std::vector<TypeInfo>&& second
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(
				const TypeInfoEnum cat,
				TypeInfo&& ext,
				std::vector<TypeInfo>&& first,
				std::vector<TypeInfo>&& second
			)
			{
				category = cat;
				single_extension = new TypeInfo(ext);
				first_group = first;
				second_group = second;
			}

			TypeInfo::TypeInfo(const size_t index)
			{
				category = TypeInfoEnum::generic;
				generic_index = index;
			}

			TypeInfo::TypeInfo(
				const TypeInfo& other,
				const std::string& label
			)
			{
				category = other.category;

				if (other.single_extension != nullptr)
					single_extension = new TypeInfo(*other.single_extension);

				first_group = other.first_group;
				second_group = second_group;
				generic_index = other.generic_index;
				lbl = label;
			}

			TypeInfo::TypeInfo(
				TypeInfo&& other,
				const std::string& label
			)
			{
				category = other.category;

				single_extension = other.single_extension;
				other.single_extension = nullptr;

				first_group = std::move(other.first_group);
				second_group = std::move(other.second_group);
				generic_index = std::move(other.generic_index);
				lbl = label;
			}

			TypeInfo::TypeInfo(
				const TypeInfo& other,
				std::string&& label
			)
			{
				category = other.category;

				if (other.single_extension != nullptr)
					single_extension = new TypeInfo(*other.single_extension);

				first_group = other.first_group;
				second_group = second_group;
				generic_index = other.generic_index;
				lbl = label;
			}

			TypeInfo::TypeInfo(
				TypeInfo&& other,
				std::string&& label
			)
			{
				category = other.category;

				single_extension = other.single_extension;
				other.single_extension = nullptr;

				first_group = std::move(other.first_group);
				second_group = std::move(other.second_group);
				generic_index = std::move(other.generic_index);
				lbl = label;
			}

			TypeInfo::TypeInfo()
			{
				category = TypeInfoEnum::none;
			}

			TypeInfo::TypeInfo(const TypeInfo& other)
			: TypeInfo(other, other.lbl)
			{}

			TypeInfo::TypeInfo(TypeInfo&& other)
			: TypeInfo(other, std::move(other.lbl))
			{}

			TypeInfo& TypeInfo::operator=(const TypeInfo& other)
			{
				category = other.category;

				delete single_extension;
				if (other.single_extension == nullptr)
					single_extension = nullptr;
				else
					single_extension = new TypeInfo(*other.single_extension);

				first_group = other.first_group;
				second_group = other.second_group;
				generic_index = other.generic_index;
				lbl = other.lbl;

				return *this;
			}

			TypeInfo& TypeInfo::operator=(TypeInfo&& other)
			{
				category = other.category;

				delete single_extension;
				single_extension = other.single_extension;
				other.single_extension = nullptr;

				first_group = std::move(other.first_group);
				second_group = std::move(other.second_group);
				generic_index = other.generic_index;
				lbl = std::move(other.lbl);

				return *this;
			}

			bool TypeInfo::operator==(const TypeInfo& other) const
			{
				TypeInfo a = simplify(*this);
				TypeInfo b = simplify(other);

				if (a.category != b.category)
					return false;

				if (a.single_extension != nullptr)
					if (b.single_extension != nullptr)
						if (*a.single_extension != *b.single_extension)
							return false;
						else
							;
					else
						return false;
				else
					if (b.single_extension == nullptr)
						return false;

				if (a.first_group != b.first_group)
					return false;

				if (a.second_group != b.second_group)
					return false;

				if (a.generic_index != b.generic_index)
					return false;

				if (a.lbl != b.lbl)
					return false;

				return true;
			}

			bool TypeInfo::operator!=(const TypeInfo& other) const
			{
				return not (*this == other);
			}

			bool TypeInfo::is_equivalent(const TypeInfo& other) const
			{
				TypeInfo a = simplify(*this);
				TypeInfo b = simplify(other);

				if (a.category != b.category)
					return false;

				if (a.single_extension != nullptr)
					if (b.single_extension != nullptr)
						if (
							not (*a.single_extension).is_equivalent(
								*b.single_extension
							)
						   )
							return false;
						else;
					else
						return false;
				else
					if (b.single_extension == nullptr)
						return false;

				if (a.first_group.size() != b.first_group.size())
					return false;
				for (size_t i = 0; i < a.first_group.size(); ++i)
					if (
						not a.first_group[i].is_equivalent(
							b.first_group[i]
						 )
					   )
						return false;

				if (a.second_group.size() != b.second_group.size())
					return false;
				for (size_t i = 0; i < a.second_group.size(); ++i)
					if (
						not a.second_group[i].is_equivalent(
							b.second_group[i]
						)
					   )
						return false;

				if (a.generic_index != b.generic_index)
					return false;

				return true;
			}

			TypeInfo TypeInfo::specialize(const std::vector<TypeInfo>& types) const
			{
				return TypeInfo(TypeInfoEnum::specialize, *this, types);
			}

			TypeInfo TypeInfo::specialize(std::vector<TypeInfo>&& types) const
			{
				return TypeInfo(TypeInfoEnum::specialize, *this, types);
			}

			TypeInfo TypeInfo::labeled(const std::string& lbl) const
			{
				return TypeInfo(*this, lbl);
			}

			TypeInfo TypeInfo::labeled(std::string&& lbl) const
			{
				return TypeInfo(*this, lbl);
			}

			bool TypeInfo::has_label() const
			{
				return lbl != "";
			}

			const std::string& TypeInfo::label() const
			{
				return lbl;
			}

			bool TypeInfo::is_specialization() const
			{
				return category == TypeInfoEnum::specialize;
			}

			const TypeInfo& TypeInfo::specialization_template() const
			{
				return  *single_extension;
			}

			const std::vector<TypeInfo>& TypeInfo::specialization_parameters() const
			{
				return first_group;
			}

			bool TypeInfo::is_list() const
			{
				return category == TypeInfoEnum::list;
			}

			const TypeInfo& TypeInfo::list_of() const
			{
				return *single_extension;
			}

			bool TypeInfo::is_tuple() const
			{
				return category == TypeInfoEnum::tuple;
			}

			const std::vector<TypeInfo>& TypeInfo::tuple_types() const
			{
				return first_group;
			}

			bool TypeInfo::is_repeated_tuple() const
			{
				if (not is_tuple())
					return false;

				if (first_group.size() == 0)
					return false;

				TypeInfo first;
				bool is_first;

				for (const auto& i : first_group)
					if (is_first)
					{
						first = i;
						is_first = true;
					}
					else
						if (i != first)
							return false;
				return true;
			}

			const TypeInfo& TypeInfo::repeated_tuple_of() const
			{
				return first_group[0];
			}

			size_t TypeInfo::repeated_tuple_length() const
			{
				return first_group.size();
			}

			bool TypeInfo::is_generic_parameter() const
			{
				return category == TypeInfoEnum::generic;
			}

			size_t TypeInfo::generic_parameter_index() const
			{
				return generic_index;
			}

			size_t TypeInfo::is_generic() const
			{
				if (is_generic_parameter())
					return true;

				if (single_extension != nullptr)
					if ((*single_extension).is_generic())
						return true;

				for (const auto& i : first_group)
					if (i.is_generic())
						return true;

				for (const auto& i : second_group)
					if (i.is_generic())
						return true;

				return false;
			}

			bool TypeInfo::is_function() const
			{
				return category == TypeInfoEnum::function;
			}

			const TypeInfo& TypeInfo::function_return_type() const
			{
				return *single_extension;
			}

			const std::vector<TypeInfo>& TypeInfo::function_arguments() const
			{
				return first_group;
			}

			bool TypeInfo::is_code() const
			{
				return category == TypeInfoEnum::code;
			}

			const std::vector<TypeInfo>& TypeInfo::code_inputs() const
			{
				return first_group;
			}

			const std::vector<TypeInfo>& TypeInfo::code_outputs() const
			{
				return second_group;
			}

			bool TypeInfo::is_union() const
			{
				return category == TypeInfoEnum::type_union;
			}

			const std::vector<TypeInfo>& TypeInfo::union_options() const
			{
				return first_group;
			}

			const TypeInfo TypeInfo::boolean = TypeInfoEnum::boolean;

			const TypeInfo TypeInfo::integer = TypeInfoEnum::integer;

			const TypeInfo TypeInfo::number = TypeInfoEnum::number;

			const TypeInfo TypeInfo::any = TypeInfoEnum::any;

			const TypeInfo TypeInfo::string = TypeInfoEnum::string;

			TypeInfo TypeInfo::list(const TypeInfo& of)
			{
				return TypeInfo(TypeInfoEnum::list, of);
			}

			TypeInfo TypeInfo::list(TypeInfo&& of)
			{
				return TypeInfo(TypeInfoEnum::list, of);
			}

			TypeInfo TypeInfo::tuple(
				const TypeInfo& of,
				const size_t times
			)
			{
				return TypeInfo(
					TypeInfoEnum::tuple,
					std::vector<TypeInfo>(times, of)
				);
			}

			TypeInfo TypeInfo::tuple(
				TypeInfo&& of,
				const size_t times
			)
			{
				return TypeInfo(
					TypeInfoEnum::tuple,
					std::vector<TypeInfo>(times, of)
				);
			}

			TypeInfo TypeInfo::tuple(const std::vector<TypeInfo>& types)
			{
				return TypeInfo(TypeInfoEnum::tuple, types);
			}

			TypeInfo TypeInfo::tuple(std::vector<TypeInfo>&& types)
			{
				return TypeInfo(TypeInfoEnum::tuple, types);
			}

			TypeInfo TypeInfo::generic_parameter(const size_t index)
			{
				return TypeInfo(index);
			}

			TypeInfo TypeInfo::function(
				const TypeInfo& ret,
				const std::vector<TypeInfo>& args
			)
			{
				return TypeInfo(TypeInfoEnum::function, ret, args);
			}

			TypeInfo TypeInfo::function(
				TypeInfo&& ret,
				const std::vector<TypeInfo>& args
			)
			{
				return TypeInfo(TypeInfoEnum::function, ret, args);
			}

			TypeInfo TypeInfo::function(
				const TypeInfo& ret,
				std::vector<TypeInfo>&& args
			)
			{
				return TypeInfo(TypeInfoEnum::function, ret, args);
			}

			TypeInfo TypeInfo::function(
				TypeInfo&& ret,
				std::vector<TypeInfo>&& args
			)
			{
				return TypeInfo(TypeInfoEnum::function, ret, args);
			}

			TypeInfo TypeInfo::code(
				const std::vector<TypeInfo>& inputs,
				const std::vector<TypeInfo>& outputs
			)
			{
				return TypeInfo(TypeInfoEnum::code, inputs, outputs);
			}

			TypeInfo TypeInfo::code(
				std::vector<TypeInfo>&& inputs,
				const std::vector<TypeInfo>& outputs
			)
			{
				return TypeInfo(TypeInfoEnum::code, inputs, outputs);
			}

			TypeInfo TypeInfo::code(
				const std::vector<TypeInfo>& inputs,
				std::vector<TypeInfo>&& outputs
			)
			{
				return TypeInfo(TypeInfoEnum::code, inputs, outputs);
			}

			TypeInfo TypeInfo::code(
				std::vector<TypeInfo>&& inputs,
				std::vector<TypeInfo>&& outputs
			)
			{
				return TypeInfo(TypeInfoEnum::code, inputs, outputs);
			}

			TypeInfo TypeInfo::type_union(const std::vector<TypeInfo>& options)
			{
				return TypeInfo(TypeInfoEnum::type_union, options);
			}

			TypeInfo TypeInfo::type_union(std::vector<TypeInfo>&& options)
			{
				return TypeInfo(TypeInfoEnum::type_union, options);
			}

			const TypeInfo TypeInfo::none = TypeInfoEnum::none;

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

			const TypeInfo TypeInfo::interactable = TypeInfo::function(
				TypeInfo::tuple({
					TypeInfo::boolean,
					TypeInfo::function(  // drag
						TypeInfo::list(TypeInfo::any),
						{TypeInfo::position}
					),
					TypeInfo::renderable  // hover
				}),
				{TypeInfo::position}
			).labeled("interactable");

            TypeInfo::~TypeInfo()
			{
				delete single_extension;
			}
		}


		const Value none = Nothing();


		TypeInfo simplify(const TypeInfo& t)
		{
			return apply_specialization(t, {});
		}


		TypeInfo apply_specialization(
			const TypeInfo& t,
			const std::vector<TypeInfo>& args
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

				return TypeInfo::function(
					apply_specialization(t.function_return_type(), args),
					args2
				);
			}
			else if (t.is_specialization())
				return apply_specialization(
					t.specialization_template(),
					t.specialization_parameters()
				);
			else if (t.is_generic_parameter())
				return args[t.generic_parameter_index()];
			else
				return t;
		}


		std::string to_string(const std::vector<TypeInfo>& ts)
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
			{TypeInfo::any, "any"},
			{TypeInfo::none, "none"}
		};


		std::string to_string(const TypeInfo& t)
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
			else if (t.is_union())
				return "union[" + to_string(t.union_options()) + "]";
			else
				return names.find(t)->second;
		}
	}
}


size_t combine_hashes(std::vector<size_t>& hashes)
{
	size_t out = 0;

	for (const auto& i : hashes)
		out ^= i;

	return out;
}


using TypeInfo = doanimate::types::TypeInfo;


namespace std
{
	size_t hash<TypeInfo>::operator()(const TypeInfo& t) const
	{
		if (t == TypeInfo::boolean)
			return 1;
		else if (t == TypeInfo::integer)
			return 3;
		else if (t == TypeInfo::number)
			return 5;
		else if (t == TypeInfo::string)
			return 7;
		else if (t == TypeInfo::any)
			return 9;
		else if (t == TypeInfo::none)
			return 11;
		else
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
	}
}
