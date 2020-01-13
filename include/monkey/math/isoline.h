#pragma once

#include <vector>
#include <map>
#include <monkey/math/piecewise.h>

class IsoLine : public Function2D {
public:
    IsoLine ();
    void addIsoDepthLine (const std::vector<float>&, float z);
    virtual float operator()(float x, float y) override;

private:
    std::vector <PiecewiseLinearFunction> m_isoDepthLines;
    std::vector <float> m_z;
};