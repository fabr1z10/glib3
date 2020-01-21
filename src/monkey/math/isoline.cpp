#include <monkey/math/isoline.h>
#include <iostream>
IsoLine::IsoLine() {

}

void IsoLine::addIsoDepthLine(const std::vector<float> & points, float z) {

    PiecewiseLinearFunction func;

    for (size_t i=0; i < points.size(); i+=2) {
        func.addNode(points[i], points[i+1]);
    }
    m_isoDepthLines.push_back(func);
    m_z.push_back(z);
}


float IsoLine::operator()(float x, float y) {
    // find the two iso-lines containing the point
    size_t i = 0;
    float z1 = 0;
    float y1 = 0;
    for (; i <m_isoDepthLines.size(); ++i) {
        y1 = m_isoDepthLines[i].operator()(x);
        if (y1 > y) {
            break;
        }
    }
    z1 = m_z[i];
    float z0 = m_z[i-1];
    // now i contains the index of the isoline above the point
    float y0 = m_isoDepthLines[i-1].operator()(x);

    float z = z0 + (z1-z0) * ((y - y0)/ (y1 - y0));
    std::cout << i << "." << x << "-" << y << "-" << z << "\n";
    return z;
}