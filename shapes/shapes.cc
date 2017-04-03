#include "shapes.hh"
#include <cmath>
#include <tuple>


namespace doanimate {
    namespace shapes {
        std::vector<types::Value> transparent {
            0.0,
            0.0,
            0.0,
            0.0
        };


        std::pair<double, double> get_position(const types::Value v) {
            auto vec = boost::get<std::vector<types::Value>>(v);
            return {boost::get<double>(vec[0]), boost::get<double>(vec[1])};
        }


        double square(double x) {
            return x * x;
        }

        bool on_line(
            std::pair<double, double> p1,
            std::pair<double, double> v,
            double l,
            double w,
            std::pair<double, double> q
        ) {
            // see shapes.ipynb
            std::pair<double, double> u = {
                q.first - p1.first,
                q.second - p1.second
            };
            double m = (
                v.first * u.first +
                v.second * u.second
            ) / (l * l);
            if (m < 0 or m > l)
                return false;
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
                return true;
            else
                return false;
        }


        nodes::Node* line() {
            return new nodes::DefaultNode(
                [](std::vector<types::Value> args) -> std::vector<types::Value> {
                    auto p1 = get_position(args[0]);
                    auto p2 = get_position(args[1]);
                    double w = boost::get<double>(args[2]);
                    types::Value c = args[3];
                    std::pair<double, double> v = {
                        p2.first - p1.first,
                        p2.second - p1.second
                    };
                    double l = std::sqrt(v.first * v.first + v.second * v.second);

                    auto on_shape = [=](std::pair<double, double> q) -> bool {
                        return on_line(p1, v, l, w, q);
                    };

                    return {
                        types::representations::Function(
                            [=](std::vector<types::Value> args)
                            -> types::Value {
                                return on_shape(
                                    get_position(args[0])
                                )? c : transparent;
                            },
                            types::TypeInfo::renderable
                        ),
                        types::representations::Function(
                            [=](std::vector<types::Value>)
                            -> types::Value {
                                // TODO
                                return types::representations::Tuple{
                                    false,
                                    types::representations::Function(
                                        [](std::vector<types::Value>)
                                        -> void {
                                        }, {types::TypeInfo::position, types::TypeInfo::position}
                                    ),
                                    types::representations::Function(
                                        [](std::vector<types::Value>) {
                                            return transparent;
                                        },
                                        types::TypeInfo::renderable
                                    )
                                };
                            },
                            types::TypeInfo::interactable
                        )
                    };
                }, {
                    types::TypeInfo::position,
                    types::TypeInfo::position,
                    types::TypeInfo::number,
                    types::TypeInfo::color
                }, {"from", "to", "thickness", "color"}, {types::TypeInfo::renderable, types::TypeInfo::interactable}, {"image", "editor"}
            );
        }

        nodes::Node* polygon() {
            return new nodes::DefaultNode(
                [](std::vector<types::Value> args) -> std::vector<types::Value> {
                    auto _p = boost::get<std::vector<types::Value>>(args[0]);
                    std::vector<std::pair<double, double>> points(_p.size());
                    for (size_t i = 0; i < _p.size(); ++i)
                        points[i] = get_position(_p[i]);
                    std::vector<std::pair<double, double>> vecs(points.size());
                    for (size_t i = 0; i < points.size() - 1; ++i)
                        vecs[i] = {
                            points[i + 1].first - points[i].first,
                            points[i + 1].second - points[i].second
                        };
                    if (points.size() > 0)
                        vecs[points.size() - 1] = {
                            points[0].first -
                            points[points.size() - 1].first,
                            points[0].second -
                            points[points.size() - 1].second
                        };
                    std::vector<double> lengths(vecs.size());
                    for (size_t i = 0; i < vecs.size(); ++i)
                        lengths[i] = std::sqrt(
                            square(vecs[i].first) + square(vecs[i].second)
                        );
                    auto fill = args[1];
                    double width = boost::get<double>(args[2]);
                    auto stroke = args[3];

                    auto in_shape = [=](std::pair<double, double> q) -> bool {
                        // see shapes.ipynb
                        bool in_shape_ray_a = false;
                        bool in_shape_ray_b = false;
                        for (size_t i = 0; i < points.size(); ++i) {
                            auto p1 = (i == 0)?
                                points[points.size() - 1] :
                                points[i];
                            auto p2 = points[i];
                            if (
                                (
                                     p1.first < q.first and
                                    p2.first > q.first
                                ) or
                                (
                                     p1.first > q.first and
                                    p2.first < q.first
                                )
                               ) {
                                // m = delta y / delta x
                                // y2 = m*x2 + n | - m*x2
                                // n = y2 - m*x2
                                // -> f(x) = (x - x2) * delta y /
                                //           delta x + y2
                                double delta_x = p2.first - p1.first;
                                double delta_y = p2.second - p1.second;
                                double intersection_y =
                                    (q.first - p2.first) * delta_y /
                                    delta_x + p2.second;
                                if (intersection_y > q.second)
                                    in_shape_ray_a = not in_shape_ray_a;
                                else if (intersection_y < q.second)
                                    in_shape_ray_b = not in_shape_ray_b;
                            }
                        }
                        return in_shape_ray_a and in_shape_ray_b;
                    };

                    auto on_shape = [=](std::pair<double, double> q) -> bool {
                        for (size_t i = 0; i < points.size(); ++i)
                            if (
                                on_line(
                                    points[i],
                                    vecs[i],
                                    lengths[i],
                                    width,
                                    q
                                )
                               )
                                return true;
                        return false;
                    };

                    return {
                        types::representations::Function(
                            [=](std::vector<types::Value> args)
                            -> types::Value {
                                auto q = get_position(args[0]);
                                if (on_shape(q))
                                    return stroke;
                                return in_shape(q)? fill : transparent;
                            },
                            types::TypeInfo::renderable
                        ),
                        types::representations::Function(
                            [=](std::vector<types::Value>)
                            -> types::Value {
                                // TODO
                                return types::representations::Tuple{
                                    false,
                                    types::representations::Function(
                                        [](std::vector<types::Value>)
                                        -> void {
                                        }, {types::TypeInfo::position, types::TypeInfo::position}
                                    ),
                                    types::representations::Function(
                                        [](std::vector<types::Value>) {
                                            return transparent;
                                        },
                                        types::TypeInfo::renderable
                                    )
                                };
                            },
                            types::TypeInfo::interactable
                        )
                    };
                }, {
                    types::TypeInfo::list(types::TypeInfo::position),
                    types::TypeInfo::color,
                    types::TypeInfo::number,
                    types::TypeInfo::color
                }, {"points", "fill", "thickness", "stroke"}, {types::TypeInfo::renderable, types::TypeInfo::interactable}, {"image", "editor"}
            );
        }
    }
}
