#pragma once

namespace glib3::math {

    /**
     * Solve a quadratic equation ax^2 + bx + c = 0
     * Returns only REAL Values
     */
    bool solve_quadratic (double a, double b, double c, double& x1, double &x2);
}