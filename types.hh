#ifndef	types_hh
#define types_hh
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


		implementation::TypeInfo simplify(const implementation::TypeInfo&);


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

				TypeInfo(const TypeInfoEnum cat);

				TypeInfo(
					const TypeInfoEnum cat,
					const TypeInfo& ext
				);

				TypeInfo(
					const TypeInfoEnum cat,
					TypeInfo&& ext
				);

				TypeInfo(
					const TypeInfoEnum cat,
					const std::vector<TypeInfo>& group
				);

				TypeInfo(
					const TypeInfoEnum cat,
					std::vector<TypeInfo>&& group
				);

				TypeInfo(
					const TypeInfoEnum cat,
					const TypeInfo& ext,
					const std::vector<TypeInfo>& group
				);

				TypeInfo(
					const TypeInfoEnum cat,
					TypeInfo&& ext,
					const std::vector<TypeInfo>& group
				);

				TypeInfo(
					const TypeInfoEnum cat,
					const TypeInfo& ext,
					std::vector<TypeInfo>&& group
				);

				TypeInfo(
					const TypeInfoEnum cat,
					TypeInfo&& ext,
					std::vector<TypeInfo>&& group
				);

				TypeInfo(
					const TypeInfoEnum cat,
					const std::vector<TypeInfo>& first,
					const std::vector<TypeInfo>& second
				);

				TypeInfo(
					const TypeInfoEnum cat,
					std::vector<TypeInfo>&& first,
					const std::vector<TypeInfo>& second
				);

				TypeInfo(
					const TypeInfoEnum cat,
					const std::vector<TypeInfo>& first,
					std::vector<TypeInfo>&& second
				);

				TypeInfo(
					const TypeInfoEnum cat,
					std::vector<TypeInfo>&& first,
					std::vector<TypeInfo>&& second
				);

				TypeInfo(
					const TypeInfoEnum cat,
					const TypeInfo& ext,
					const std::vector<TypeInfo>& first,
					const std::vector<TypeInfo>& second
				);

				TypeInfo(
					const TypeInfoEnum cat,
					TypeInfo&& ext,
					const std::vector<TypeInfo>& first,
					const std::vector<TypeInfo>& second
				);

				TypeInfo(
					const TypeInfoEnum cat,
					const TypeInfo& ext,
					std::vector<TypeInfo>&& first,
					const std::vector<TypeInfo>& second
				);

				TypeInfo(
					const TypeInfoEnum cat,
					TypeInfo&& ext,
					std::vector<TypeInfo>&& first,
					const std::vector<TypeInfo>& second
				);

				TypeInfo(
					const TypeInfoEnum cat,
					const TypeInfo& ext,
					const std::vector<TypeInfo>& first,
					std::vector<TypeInfo>&& second
				);

				TypeInfo(
					const TypeInfoEnum cat,
					TypeInfo&& ext,
					const std::vector<TypeInfo>& first,
					std::vector<TypeInfo>&& second
				);

				TypeInfo(
					const TypeInfoEnum cat,
					const TypeInfo& ext,
					std::vector<TypeInfo>&& first,
					std::vector<TypeInfo>&& second
				);

				TypeInfo(
					const TypeInfoEnum cat,
					TypeInfo&& ext,
					std::vector<TypeInfo>&& first,
					std::vector<TypeInfo>&& second
				);

				TypeInfo(const size_t index);

				TypeInfo(
					const TypeInfo& other,
					const std::string& label
				);

				TypeInfo(
					TypeInfo&& other,
					const std::string& label
				);

				TypeInfo(
					const TypeInfo& other,
					std::string&& label
				);

				TypeInfo(
					TypeInfo&& other,
					std::string&& label
				);

				public:
				TypeInfo();

				TypeInfo(const TypeInfo& other);

				TypeInfo(TypeInfo&& other);

				TypeInfo& operator=(const TypeInfo& other);

				TypeInfo& operator=(TypeInfo&& other);

				bool operator==(const TypeInfo& other) const;

				bool operator!=(const TypeInfo& other) const;

				bool is_equivalent(const TypeInfo& other) const;

				TypeInfo specialize(const std::vector<TypeInfo>& types) const;

				TypeInfo specialize(std::vector<TypeInfo>&& types) const;

				TypeInfo labeled(const std::string& lbl) const;

				TypeInfo labeled(std::string&& lbl) const;

				bool has_label() const;

				const std::string& label() const;

				bool is_specialization() const;

				const TypeInfo& specialization_template() const;

				const std::vector<TypeInfo>& specialization_parameters() const;

				bool is_list() const;

				const TypeInfo& list_of() const;

				bool is_tuple() const;

				const std::vector<TypeInfo>& tuple_types() const;

				bool is_repeated_tuple() const;

				const TypeInfo& repeated_tuple_of() const;

				size_t repeated_tuple_length() const;

				bool is_generic_parameter() const;

				size_t generic_parameter_index() const;

				size_t is_generic() const;

				bool is_function() const;

				const TypeInfo& function_return_type() const;

				const std::vector<TypeInfo>& function_arguments() const;

				bool is_code() const;

				const std::vector<TypeInfo>& code_inputs() const;

				const std::vector<TypeInfo>& code_outputs() const;

				static const TypeInfo boolean;
				static const TypeInfo integer;
				static const TypeInfo number;
				static const TypeInfo any;
				static const TypeInfo string;

				static TypeInfo list(const TypeInfo& of);

				static TypeInfo list(TypeInfo&& of);

				static TypeInfo tuple(
					const TypeInfo& of,
					const size_t times
				);

				static TypeInfo tuple(
					TypeInfo&& of,
					const size_t times
				);

				static TypeInfo tuple(const std::vector<TypeInfo>& types);

				static TypeInfo tuple(std::vector<TypeInfo>&& types);

				static TypeInfo generic_parameter(const size_t index);

				static TypeInfo function(
					const TypeInfo& ret,
					const std::vector<TypeInfo>& args
				);

				static TypeInfo function(
					TypeInfo&& ret,
					const std::vector<TypeInfo>& args
				);

				static TypeInfo function(
					const TypeInfo& ret,
					std::vector<TypeInfo>&& args
				);

				static TypeInfo function(
					TypeInfo&& ret,
					std::vector<TypeInfo>&& args
				);

				static TypeInfo code(
					const std::vector<TypeInfo>& inputs,
					const std::vector<TypeInfo>& outputs
				);

				static TypeInfo code(
					std::vector<TypeInfo>&& inputs,
					const std::vector<TypeInfo>& outputs
				);

				static TypeInfo code(
					const std::vector<TypeInfo>& inputs,
					std::vector<TypeInfo>&& outputs
				);

				static TypeInfo code(
					std::vector<TypeInfo>&& inputs,
					std::vector<TypeInfo>&& outputs
				);

				static const TypeInfo none;
				static const TypeInfo position;
				static const TypeInfo position2d;
				static const TypeInfo position3d;
				static const TypeInfo color;
				static const TypeInfo color_without_alpha;
				static const TypeInfo renderable;
				static const TypeInfo sound;

				~TypeInfo();

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
			const TypeInfo&,
			const std::vector<TypeInfo>&
		);


		std::string to_string(const TypeInfo&);
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
