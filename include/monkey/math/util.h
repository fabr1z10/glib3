#pragma once

#include <string>
#include <unordered_map>

namespace glib3::math {

    /**
     * Solve a quadratic equation ax^2 + bx + c = 0
     * Returns only REAL Values
     */
    bool solve_quadratic (double a, double b, double c, double& x1, double &x2);

    float parse_expr(const std::string&, std::unordered_map<std::string, float> vars = std::unordered_map<std::string, float>());
}