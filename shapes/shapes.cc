#include "shapes.hh"
#include <cmath>
#include <tuple>


namespace doanimate
{
	namespace shapes
	{
		std::vector<types::Value> transparent {
			0.0,
			0.0,
			0.0,
			0.0
		};


		std::pair<double, double> get_position(const types::Value v)
		{
			auto vec = boost::get<std::vector<types::Value>>(v);
			return {boost::get<double>(vec[0]), boost::get<double>(vec[1])};
		}


		double square(double x) {
			return x * x;
		}


		nodes::Node* line()
		{
			return new nodes::DefaultNode(
				[](std::vector<types::Value> args) -> std::vector<types::Value>
				{
					auto p1 = get_position(args[0]);
					auto p2 = get_position(args[1]);
					double w = boost::get<double>(args[2]);
					types::Value c = args[3];
					std::pair<double, double> v = {
						p2.first - p1.first,
						p2.second - p1.second
					};
					double l = std::sqrt(v.first * v.first + v.second * v.second);

					return {
						types::representations::Function(
							[=](std::vector<types::Value> args)
							-> types::Value
							{
								auto q = get_position(args[0]);
								// see shapes.md
								std::pair<double, double> u = {
									q.first - p1.first,
									q.second - p1.second
								};
								double m = (
									v.first * u.first +
									v.second * u.second
								) / l;
								if (m < 0 or m > l)
									return transparent;
								double d = std::sqrt(
									square(
									 	u.first -
										m * v.first
									) +
									square(
										u.second -
										m * v.second
									)
								);
								if (d < w)
									return c;
								else
									return transparent;
							}
						)
						// TODO: interactable
					};
				},
				{
					types::TypeInfo::position,
					types::TypeInfo::position,
					types::TypeInfo::number,
					types::TypeInfo::color
				},
				{"from", "to", "thickness", "color"},
				{types::TypeInfo::renderable, types::TypeInfo::interactable},
				{"image", "editor"}
			);
		}
	}
}
