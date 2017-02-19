#include "node_system.hh"


namespace doanimate
{
	namespace nodes
	{
		NodeSystem::iterator NodeSystem::begin()
		{
			return iterator(nodes.begin(), nodes.end());
		}

		NodeSystem::iterator NodeSystem::end()
		{
			return iterator(nodes.end(), nodes.end());
		}

		NodeSystem::const_iterator NodeSystem::cbegin() const
		{
			return const_iterator(nodes.cbegin(), nodes.cend());
		}

		NodeSystem::const_iterator NodeSystem::cend() const
		{
			return const_iterator(nodes.cbegin(), nodes.cend());
		}

		NodeSystem::const_iterator NodeSystem::begin() const
		{
			return cbegin();
		}

		NodeSystem::const_iterator NodeSystem::end() const
		{
			return cend();
		}

		NodeWrapper& NodeSystem::at(size_t index)
		{
			return nodes[index].get();
		}

		void NodeSystem::remove(NodeSystem::iterator it)
		{
			*(it.current) = boost::none;
		}

		void NodeSystem::remove(const size_t index)
		{
			nodes[index] = boost::none;
		}

		size_t NodeSystem::add(Node* n)
		{
			size_t index = 0;

			for (auto& i : nodes)
				if (i == boost::none)
				{
					i = NodeWrapper(n);
					return index;
				}
				else
					++ index;

			nodes.push_back(NodeWrapper(n));

			return nodes.size() - 1;
		}

		void NodeSystem::quick_add(Node* n)
		{
			nodes.push_back(NodeWrapper(n));
		}

		void NodeSystem::rerun(
			const std::unordered_set<size_t> source,
			const bool skip_first_stage
		)
		{
			std::unordered_set<size_t> done;
			size_t alive = 0;

			for (const auto& i : nodes)
				if (i != boost::none)
					++ alive;

			if (!skip_first_stage)
			{
				std::unordered_set<size_t> visited = source;

				while (visited.size() != alive)
				{
					size_t index = -1;

					for (const auto& i : nodes)
					{
						++ index;

						if (i != boost::none)
						{
							bool dependencies_not_visited = false;
							bool needs_computation = false;

							for (const auto& j : i.get().input_links)
								if (j.first != size_t(-1))
								{
									if (
										visited.find(j.first) ==
										visited.end()
									   )
									{
										dependencies_not_visited
											= true;
										break;
									}
									else if (
										done.find(j.first) ==
										done.end()
									        )
									{
										needs_computation = true;
										break;
									}
								}

							if (dependencies_not_visited)
								continue;
							else
							{
								visited.insert(index);
								if (!needs_computation)
									done.insert(index);
							}
						}
					}
				}
			}

			while (done.size() != alive)
			{
				size_t index = -1;
				for (const auto& i : nodes)
				{
					++ index;
					if (i != boost::none)
					{
						bool ready = true;

						for (const auto& j : i.get().input_links)
							if (j.first != size_t(-1))
								if (done.find(j.first) == done.end())
								{
									ready = false;
									break;
								}

						if (ready)
						{
							Node* n = i.get().n;
							auto& vec = n->get_inputs();
							size_t index2 = -1;

							for (const auto& i : i.get().input_links)
							{
								++ index2;

								if (i.first != size_t(-1))
									vec[index2] = nodes[
										i.first
									].get().n->get_outputs()[
										i.second
									];
							}
							n->update();

							done.insert(index);
						}
					}
				}
			}
		}

		void NodeSystem::rerun(const std::unordered_set<NodeSystem::iterator*> source)
		{
			std::unordered_set<size_t> out(source.bucket_count());

			for (auto& i : source)
				out.insert(i->index());

			rerun(out);
		}

		void NodeSystem::rerun()
		{
			rerun(std::unordered_set<size_t>{}, true);
		}

		bool NodeSystem::would_create_cycle(
			const size_t node,
			const std::pair<size_t, size_t> connection
		) const
		{
			std::unordered_set<size_t> dependencies;
			std::unordered_set<size_t> level{connection.first};

			if (connection.first == node)
				return true;

			for (const auto& i : nodes[node].get().input_links)
				if (i.first != size_t(-1))
					level.insert(i.first);

			while (true)
			{
				if (level.find(node) != level.end())
					return true;

				bool dependency_added = false;
				std::unordered_set<size_t> next_level;

				for (const auto& i : level)
					for (const auto& j : nodes[i].get().input_links)
						if (j.first != size_t(-1))
							if (dependencies.find(j.first) ==
									dependencies.end())
							{
								dependency_added = true;
								next_level.insert(j.first);
							}

				if (!dependency_added)
					return false;

				for (const auto& i : next_level)
					dependencies.insert(i);

				level = next_level;
			}
		}

		void NodeSystem::force_connection(
			const size_t node,
			const size_t index,
			const std::pair<size_t, size_t> connection
		)
		{
			nodes[node].get().input_links[index] = connection;
		}

		bool NodeSystem::create_connection(
			const size_t node,
			const size_t index,
			const std::pair<size_t, size_t> connection
		)
		{
			if (!would_create_cycle(node, connection))
			{
				force_connection(node, index, connection);
				return true;
			}

			return false;
		}
	}
}
