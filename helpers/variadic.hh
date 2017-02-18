#include <vector>
#include <unordered_set>


namespace helpers {
	namespace implementation {
		template <typename T>
			void fill_set(std::unordered_set<T>&) {
			}

		template <typename T, typename... Ts>
			void fill_set(std::unordered_set<T>& set, T current, Ts... next) {
				set.insert(current);
				fill_set(set, next...);
			}
	}

	// TODO: to_vector

	template <typename T, typename... Ts>
		std::unordered_set<T> unordered_set_of(T& first, Ts... next) {
			std::unordered_set<T> out;
			fill_set(out, first, next...);
			return out;
		}
}
