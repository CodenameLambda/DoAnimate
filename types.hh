#ifndef	types_h
#define types_h
#include <boost/variant.hpp>
#include <vector>
#include <string>
#include <functional>


namespace doanimate
{
	namespace types
	{
		namespace implementation
		{
			class TypeInfo;
		}


		implementation::TypeInfo simplify(const implementation::TypeInfo);


		namespace implementation
		{
			enum TypeInfoEnum
			{
				boolean,
				integer,
				number,
				list,
				tuple,
				generic,
				function,
				code,
				specialize,
				any,
				string
			};


			class TypeInfo
			{
				TypeInfoEnum category;
				TypeInfo* single_extension = nullptr;
				std::vector<TypeInfo> first_group = {};
				std::vector<TypeInfo> second_group = {};
				size_t generic_index = 0;
				std::string lbl = "";

				inline TypeInfo(const TypeInfoEnum cat)
				: category(cat)
				{}

				inline TypeInfo(
					const TypeInfoEnum cat,
					TypeInfo ext
				)
				: category(cat),
				  single_extension(new TypeInfo(ext))
				{}

				inline TypeInfo(
					const TypeInfoEnum cat,
					std::vector<TypeInfo> group
				)
				: category(cat),
				  first_group(group)
				{}

				inline TypeInfo(
					const TypeInfoEnum cat,
					TypeInfo ext,
					std::vector<TypeInfo> group
				)
				: category(cat),
				  single_extension(new TypeInfo(ext)),
				  first_group(group)
				{}

				inline TypeInfo(
					const TypeInfoEnum cat,
					std::vector<TypeInfo> first,
					std::vector<TypeInfo> second
				)
				: category(cat),
				  first_group(first),
				  second_group(second)
				{}

				inline TypeInfo(
					const TypeInfoEnum cat,
					TypeInfo ext,
					std::vector<TypeInfo> first,
					std::vector<TypeInfo> second
				)
				: category(cat),
				  single_extension(new TypeInfo(ext)),
				  first_group(first),
				  second_group(second)
				{}

				inline TypeInfo(const size_t index)
				: category(TypeInfoEnum::generic),
				  generic_index(index)
				{}

				inline TypeInfo(
					const TypeInfo other,
					const std::string label
				)
				: category(other.category),
				  single_extension(
					(other.single_extension==nullptr)?
						nullptr:
						new TypeInfo(*other.single_extension)
				  ),
				  first_group(other.first_group),
				  second_group(other.second_group),
				  generic_index(other.generic_index),
				  lbl(label)
				{}

				public:
				inline TypeInfo()
				: TypeInfo(TypeInfoEnum::tuple)
				{}

				inline TypeInfo(const TypeInfo& other)
				: TypeInfo(other, other.lbl)
				{}

				inline bool operator==(const TypeInfo other) const
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

				inline bool operator!=(const TypeInfo other) const
				{
					return not (*this == other);
				}

				inline bool is_equivalent(const TypeInfo other) const
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

				inline TypeInfo specialize(const std::vector<TypeInfo> types) const
				{
					return TypeInfo(TypeInfoEnum::specialize, *this, types);
				}

				inline TypeInfo labeled(const std::string lbl) const
				{
					return TypeInfo(*this, lbl);
				}

				inline bool has_label() const
				{
					return lbl != "";
				}

				inline std::string label() const
				{
					return lbl;
				}

				inline bool is_specialization() const
				{
					return category == TypeInfoEnum::specialize;
				}

				inline TypeInfo specialization_template() const
				{
					return *single_extension;
				}

				inline std::vector<TypeInfo> specialization_parameters() const
				{
					return first_group;
				}

				inline bool is_list() const
				{
					return category == TypeInfoEnum::list;
				}

				inline TypeInfo list_of() const
				{
					return *single_extension;
				}

				inline bool is_tuple() const
				{
					return category == TypeInfoEnum::tuple;
				}

				inline std::vector<TypeInfo> tuple_types() const
				{
					return first_group;
				}

				inline bool is_repeated_tuple() const
				{
					if (not is_tuple())
						return false;

					if (*this == none)
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

				inline TypeInfo repeated_tuple_of() const
				{
					return first_group[0];
				}

				inline size_t repeated_tuple_length() const
				{
					return first_group.size();
				}

				inline bool is_generic_parameter() const
				{
					return category == TypeInfoEnum::generic;
				}

				inline size_t generic_parameter_index() const
				{
					return generic_index;
				}

				inline size_t is_generic() const
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

				inline bool is_function() const
				{
					return category == TypeInfoEnum::function;
				}

				inline TypeInfo function_return_type() const
				{
					return *single_extension;
				}

				inline std::vector<TypeInfo> function_arguments() const
				{
					return first_group;
				}

				inline bool is_code() const
				{
					return category == TypeInfoEnum::code;
				}

				inline std::vector<TypeInfo> code_inputs() const
				{
					return first_group;
				}

				inline std::vector<TypeInfo> code_outputs() const
				{
					return second_group;
				}

				static const TypeInfo boolean;
				static const TypeInfo integer;
				static const TypeInfo number;
				static const TypeInfo any;
				static const TypeInfo string;

				static inline TypeInfo list(const TypeInfo of)
				{
					return TypeInfo(TypeInfoEnum::list, of);
				}

				static inline TypeInfo tuple(
					const TypeInfo of,
					const size_t times
				)
				{
					return TypeInfo(
						TypeInfoEnum::tuple,
						std::vector<TypeInfo>(times, of)
					);
				}

				static inline TypeInfo tuple(const std::vector<TypeInfo> types)
				{
					return TypeInfo(TypeInfoEnum::tuple, types);
				}

				static inline TypeInfo generic_parameter(const size_t index)
				{
					return TypeInfo(index);
				}

				static inline TypeInfo function(
					const TypeInfo ret,
					const std::vector<TypeInfo> args
				)
				{
					return TypeInfo(TypeInfoEnum::function, ret, args);
				}

				static inline TypeInfo code(
					const std::vector<TypeInfo> inputs,
					const std::vector<TypeInfo> outputs
				)
				{
					return TypeInfo(TypeInfoEnum::code, inputs, outputs);
				}

				static const TypeInfo none;
				static const TypeInfo position;
				static const TypeInfo position2d;
				static const TypeInfo position3d;
				static const TypeInfo color;
				static const TypeInfo color_without_alpha;
				static const TypeInfo renderable;
				static const TypeInfo sound;
				static const TypeInfo interactable;

				inline ~TypeInfo()
				{
					delete single_extension;
				}

				friend struct std::hash<TypeInfo>;
			};
		}


		using TypeInfo = implementation::TypeInfo;


		using Value = boost::make_recursive_variant<
			bool,
			long int,
			double,
			std::vector<boost::recursive_variant_>,  // can hold both lists and tuples.
			std::string
		>::type;


		namespace representations
		{
			using Boolean = bool;
			using Integer = long int;
			using Number = double;
			using List = std::vector<Value>;
			using Tuple = std::vector<Value>;
			using String = std::string;
			using Function = std::function<Value(std::vector<Value>)>;
			using Code = std::function<std::vector<Value>(std::vector<Value>)>;
		}


		TypeInfo apply_specialization(
			const TypeInfo,
			const std::vector<TypeInfo>
		);


		std::string to_string(const TypeInfo);
	}
}


namespace std
{
	template <>
	struct hash<doanimate::types::TypeInfo>
	{
		size_t operator()(const doanimate::types::TypeInfo&) const;
	};
}
#endif
