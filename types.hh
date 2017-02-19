#ifndef	types_h
#define types_h
#include <boost/variant.hpp>
#include <vector>
#include <string>
#include <functional>


namespace doanimate {
	namespace types {
		namespace implementation {
			class type_info;
		}

		implementation::type_info simplify(const implementation::type_info);

		namespace implementation {
			enum type_info_enum {
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


			class type_info {
				type_info_enum category;
				type_info* single_extension = nullptr;
				std::vector<type_info> first_group = {};
				std::vector<type_info> second_group = {};
				size_t generic_index = 0;
				std::string lbl = "";

				inline type_info(const type_info_enum cat) : category(cat) {
				}

				inline type_info(const type_info_enum cat, type_info ext)
					: category(cat), single_extension(new type_info(ext)) {
				}

				inline type_info(const type_info_enum cat,
						std::vector<type_info> group)
					: category(cat), first_group(group) {
				}

				inline type_info(const type_info_enum cat, type_info ext,
						std::vector<type_info> group)
					: category(cat), single_extension(new type_info(ext)),
					  first_group(group) {
				}

				inline type_info(const type_info_enum cat,
						std::vector<type_info> first,
						std::vector<type_info> second)
					: category(cat), first_group(first), second_group(second) {
				}

				inline type_info(const type_info_enum cat, type_info ext,
						std::vector<type_info> first,
						std::vector<type_info> second)
					: category(cat), single_extension(new type_info(ext)), first_group(first), second_group(second) {
				}

				inline type_info(const size_t index)
					: category(type_info_enum::generic), generic_index(index) {
				}

				inline type_info(const type_info other, const std::string lbl)
					: category(other.category),
					  single_extension(other.single_extension),
					  first_group(other.first_group),
					  second_group(other.second_group),
					  generic_index(other.generic_index), lbl(lbl) {
				}

				public:
				inline type_info() : type_info(type_info_enum::tuple) {
				}

				inline bool operator==(const type_info other) const {
					type_info a = simplify(*this);
					type_info b = simplify(other);
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

				inline bool operator!=(const type_info other) const {
					return not (*this == other);
				}

				inline bool is_equivalent(const type_info other) const {
					type_info a = simplify(*this);
					type_info b = simplify(other);
					if (a.category != b.category)
						return false;
					if (a.single_extension != nullptr)
						if (b.single_extension != nullptr)
							if (not (*a.single_extension).is_equivalent(
										*b.single_extension
									))
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
						if (not a.first_group[i].is_equivalent(
									b.first_group[i]
								))
							return false;
					if (a.second_group.size() != b.second_group.size())
						return false;
					for (size_t i = 0; i < a.second_group.size(); ++i)
						if (not a.second_group[i].is_equivalent(
									b.second_group[i]
								))
							return false;
					if (a.generic_index != b.generic_index)
						return false;
					return true;
				}

				inline type_info specialize(const std::vector<type_info> types) const {
					return type_info(type_info_enum::specialize, *this, types);
				}

				inline type_info labeled(const std::string lbl) const {
					return type_info(*this, lbl);
				}

				inline bool has_label() const {
					return lbl != "";
				}

				inline std::string label() const {
					return lbl;
				}

				inline bool is_specialization() const {
					return category == type_info_enum::specialize;
				}

				inline type_info specialization_template() const {
					return *single_extension;
				}

				inline std::vector<type_info> specialization_parameters() const {
					return first_group;
				}

				inline bool is_list() const {
					return category == type_info_enum::list;
				}

				inline type_info list_of() const {
					return *single_extension;
				}

				inline bool is_tuple() const {
					return category == type_info_enum::tuple;
				}

				inline std::vector<type_info> tuple_types() const {
					return first_group;
				}

				inline bool is_repeated_tuple() const {
					if (not is_tuple())
						return false;
					if (*this == none)
						return false;
					type_info first;
					bool is_first;
					for (const auto& i : first_group)
						if (is_first) {
							first = i;
							is_first = true;
						}
						else
							if (i != first)
								return false;
					return true;
				}

				inline type_info repeated_tuple_of() const {
					return first_group[0];
				}

				inline size_t repeated_tuple_length() const {
					return first_group.size();
				}

				inline bool is_generic_parameter() const {
					return category == type_info_enum::generic;
				}

				inline size_t generic_parameter_index() const {
					return generic_index;
				}

				inline size_t is_generic() const {
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

				inline bool is_function() const {
					return category == type_info_enum::function;
				}

				inline type_info function_return_type() const {
					return *single_extension;
				}

				inline std::vector<type_info> function_arguments() const {
					return first_group;
				}

				inline bool is_code() const {
					return category == type_info_enum::code;
				}

				inline std::vector<type_info> code_inputs() const {
					return first_group;
				}

				inline std::vector<type_info> code_outputs() const {
					return second_group;
				}

				static const type_info boolean;
				static const type_info integer;
				static const type_info number;
				static const type_info any;
				static const type_info string;

				static inline type_info list(const type_info of) {
					return type_info(type_info_enum::list, of);
				}

				static inline type_info tuple(const type_info of, const size_t times) {
					return type_info(
							type_info_enum::tuple,
							std::vector<type_info>(times, of)
						);
				}

				static inline type_info tuple(const std::vector<type_info> types) {
					return type_info(type_info_enum::tuple, types);
				}

				static inline type_info generic_parameter(const size_t index) {
					return type_info(index);
				}

				static inline type_info function(const type_info ret,
						const std::vector<type_info> args) {
					return type_info(type_info_enum::function, ret, args);
				}

				static inline type_info code(const std::vector<type_info> inputs,
						const std::vector<type_info> outputs) {
					return type_info(type_info_enum::code, inputs, outputs);
				}

				static const type_info none;
				static const type_info position;
				static const type_info position2d;
				static const type_info position3d;
				static const type_info color;
				static const type_info color_without_alpha;
				static const type_info renderable;
				static const type_info sound;

				inline ~type_info() {
					delete single_extension;
				}

				friend struct std::hash<type_info>;
			};
		}


		using type_info = implementation::type_info;


		template <typename T>
			struct tuple {
				std::vector<T> data;

				tuple(std::vector<T> d) : data(d) {
				}

				operator std::vector<T>() const {
					return data;
				}

				std::vector<T>* operator->() {
					return &data;
				}

				std::vector<T> operator*() {
					return data;
				}
			};


		using value = boost::make_recursive_variant<
			bool,
			long int,
			double,
			std::vector<boost::recursive_variant_>,
			tuple<boost::recursive_variant_>,
			std::string
				>::type;


		namespace representations {
			using boolean = bool;
			using integer = long int;
			using number = double;
			using list = std::vector<value>;
			using tuple = tuple<value>;
			using string = std::string;
			using function = std::function<value(std::vector<value>)>;
			using code = std::function<std::vector<value>(std::vector<value>)>;
		}


		type_info apply_specialization(const type_info, const std::vector<type_info>);
		std::string to_string(const type_info);
	}
}

namespace std {
	template <>
	struct hash<doanimate::types::type_info> {
		size_t operator()(const doanimate::types::type_info&) const;
	};
}
#endif
