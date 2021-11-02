#include <monkey/math/util.h>
#include <cmath>
#include <exprtk.hpp>
#include <iostream>

#include <monkey/math/earcut.h>

bool glib3::math::solve_quadratic(double a, double b, double c, double &x1, double &x2) {

    double delta = b*b - 4*a*c;
    if (delta >= 0) {
        double sd = sqrt(delta);
        double aa = 2*a;
        x1 = (-b -sd) / aa;
        if (delta > 0) {
            x2 = (-b +sd) / aa;
        } else {
            x2 = x1;
        }
        return true;
    }
    return false;

}

float glib3::math::parse_expr(const std::string & exprString, std::unordered_map<std::string, float> vars) {
	exprtk::symbol_table<float> symbol_table;
	for (auto& variable : vars) {
		symbol_table.add_variable(variable.first, variable.second);
	}
	exprtk::expression<float> expression;
	expression.register_symbol_table(symbol_table);
	exprtk::parser<float> parser;
	if (!parser.compile(exprString, expression)) {
		std::cerr << "Compilation error...\n";
		exit(1);
	}
	return expression.value();
}

std::vector<unsigned int> glib3::math::triangulate(std::vector<std::vector<glm::vec2>> & pts) {
    using Coord = float;
    using Point = std::array<Coord, 2>;
    using N = uint32_t;

    // triangualate polygon
    std::vector<std::vector<Point>> p;
    for (const auto& vec : pts) {
        std::vector<Point> polygon;
        for (const auto& p : vec) {
            polygon.push_back({p.x, p.y});
        }
        p.push_back(polygon);
    }
    auto tri = mapbox::earcut<N>(p);
    return tri;
}