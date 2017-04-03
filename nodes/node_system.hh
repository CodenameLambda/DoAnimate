#ifndef node_node_system_hh
#define node_node_system_hh
#include <vector>
#include <tuple>
#include <unordered_set>
#include <boost/optional.hpp>
#include "../types.hh"
#include "node.hh"
#include "../helpers/variadic.hh"


namespace doanimate {
    namespace nodes {
        struct NodeWrapper {
            Node* n;
            std::vector<std::pair<size_t, size_t>> input_links;

            NodeWrapper(Node*);
        };


        class NodeSystem {
            protected:
            std::vector<boost::optional<NodeWrapper>> nodes;

            public:
            template <typename T>
            class IteratorBase {
                protected:
                T begin;
                T current;
                T end;

                IteratorBase(
                    T begin,
                    T end
                ) {
                    this->begin = begin;
                    this->current = begin;
                    this->end = end;

                    while (*current == boost::none and current != end)
                        ++ current;
                }

                public:
                IteratorBase() {}

                IteratorBase<T> operator++() {
                    ++ current;

                    while (*current == boost::none and current != end)
                        ++ current;

                    return *this;
                }

                NodeWrapper& operator*() {
                    return (*current).value();
                }

                NodeWrapper* operator->() {
                    return &*current;
                }

                size_t index() const {
                    return current - begin;
                }

                friend NodeSystem;
            };

            using iterator = IteratorBase<decltype(nodes)::iterator>;

            using const_iterator = IteratorBase<decltype(nodes)::const_iterator>;

            inline NodeSystem() {}

            iterator begin();

            iterator end();

            const_iterator cbegin() const;

            const_iterator cend() const;

            const_iterator begin() const;

            const_iterator end() const;

            NodeWrapper& at(size_t index);

            void remove(iterator it);

            void remove(const size_t index);

            size_t add(Node* n);

            void quick_add(Node* n);

            void rerun(
                const std::unordered_set<size_t>& source,
                const bool skip_first_stage = false
            );

            template <typename... Ts>
            void rerun(size_t first, Ts... data) {
                return rerun(helpers::unordered_set_of(first, data...));
            }

            void rerun(const std::unordered_set<iterator*>& source);

            template <typename... Ts>
            void rerun(iterator* first, Ts... data) {
                return rerun(helpers::unordered_set_of(first, data...));
            }

            void rerun();

            bool would_create_cycle(
                const size_t node,
                const std::pair<size_t, size_t> connection
            ) const;

            void force_connection(
                const size_t node,
                const size_t index,
                const std::pair<size_t, size_t> connection
            );

            bool create_connection(
                const size_t node,
                const size_t index,
                const std::pair<size_t, size_t> connection
            );
        };
    }
}
#endif
