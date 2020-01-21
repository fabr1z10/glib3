#include <monkey/math/integral.h>


double Integral::IntegrateTrapezoidal (double a, double b,std::function<double(double)> f, int n) {
    if (n == 1) {
        return (0.5*(b-a)*(f(a)+f(b)));
    } else {
        for (int it=1,j=1;j<n-1;j++) it <<= 1;
        double del=(b-a)/n;
        double s = f(a) + f(b);
        double x = a+del;
        for (int i = 1; i < n; ++i) {
            s += f(x);
            x += del;
        }
        s *= (0.5*del);
        return s;
    }
}
