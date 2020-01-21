#pragma once

#include <monkey/math/funcs.h>
#include <map>

class PiecewiseLinearFunction {
public:
    void addNode (float, float);
    float operator() (float x) const;
private:
    std::map<float, float> m_nodes;
};