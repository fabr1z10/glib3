#pragma once

#include <functional>

class Integral {
public:
    static double IntegrateTrapezoidal (double a, double b,std::function<double(double)> f, int N);

};