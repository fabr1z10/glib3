#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "glm/glm.hpp"


namespace glib3::math {

    /**
     * Solve a quadratic equation ax^2 + bx + c = 0
     * Returns only REAL Values
     */
    bool solve_quadratic(double a, double b, double c, double &x1, double &x2);

    float parse_expr(const std::string &,
                     std::unordered_map<std::string, float> vars = std::unordered_map<std::string, float>());

    std::vector<unsigned> triangulate(std::vector<std::vector<glm::vec2>> &);
}