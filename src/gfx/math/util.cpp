#include <gfx/math/util.h>
#include <cmath>

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