#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

// implements a linear function passing through points (x0, y0) and (x1, y1)
class LinearFunction {
public:
    LinearFunction(float x0, float y0, float x1, float y1) : m_x0{x0}, m_y0{y0}, m_y1{y1}, m_delta{(y1-y0)/(x1-x0)} {}
    float operator() (float x) {
        return m_y0 + (x - m_x0) * m_delta;
    }
private:
    float m_x0, m_y0, m_y1;
    float m_delta;

};

class Function2D {
public:
    virtual float operator()(float x, float y) = 0;

};

class PatchwiseLinear2D : public Function2D {
public:
    PatchwiseLinear2D() {}
    float operator() (float x, float y) override;
    void AddFunction (glm::vec4, bool, float value0, float value1);
private:
    std::vector<glm::vec4> m_domains;
    std::vector<bool> m_varX;
    std::vector<LinearFunction> m_functions;
};
