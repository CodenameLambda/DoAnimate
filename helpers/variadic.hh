#include <vector>
#include <unordered_set>


namespace helpers
{
	namespace implementation
	{
		template <typename T>
		void fill_set(std::unordered_set<T>&)
		{
		}


		template <typename T, typename... Ts>
		void fill_set(
			std::unordered_set<T>& set,
			T& current,
			Ts... next
		)
		{
			set.insert(current);
			fill_set(set, next...);
		}


		template <typename T>
		void fill_vector(std::vector<T>&)
		{
		}


		template <typename T, typename... Ts>
		void fill_vector(
			std::vector<T>& vec,
			T& current,
			Ts... next
		)
		{
			vec.push_back(current);
			fill_vector(vec, next...);
		}
	}


	template <typename T, typename... Ts>
	std::unordered_set<T> unordered_set_of(
		T& first,
		Ts... next
	)
	{
		std::unordered_set<T> out;
		fill_set(out, first, next...);
		return out;
	}


	template <typename T, typename... Ts>
	std::vector<T> vector_of(
		T& first,
		Ts... next
	)
	{
		std::unordered_set<T> out;
		fill_vector(out, first, next...);
		return out;
	}
}
