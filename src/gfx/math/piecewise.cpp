#include <gfx/math/piecewise.h>

void PiecewiseLinearFunction::addNode(float x, float y) {
    m_nodes.insert(std::make_pair(x, y));
}

float PiecewiseLinearFunction::operator() (float x) const {
    float last = m_nodes.rbegin()->first;
    float first = m_nodes.begin()->first;

    if (x >= last) {
        return last;
    }
    if (x <= first) {
        return first;
    }
    auto it = m_nodes.upper_bound(x);
    float x1 = it->first;
    float y1 = it->second;
    it--;
    float x0 = it->first;
    float y0 = it->second;
    return y0 + (y1 - y0)*((x - x0) / (x1- x0));
}