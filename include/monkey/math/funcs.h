#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <monkey/error.h>
#include <map>
#include <monkey/asset.h>
#include <monkey/itable.h>

class LuaTable;

// implements a linear function passing through points (x0, y0) and (x1, y1)
class LinearFunction {
public:
    LinearFunction(float x0, float y0, float x1, float y1) : m_x0{x0}, m_y0{y0},
    m_delta{(y1-y0)/(x1-x0)} {}
    float operator() (float x) {
        return m_y0 + (x - m_x0) * m_delta;
    }
    // only works if m_delta is not 0
    //float inverse(float value) {
    //    if (m_delta == 0.0f) {
    //        GLIB_FAIL("Attempting to compute inverse of a const function!");
    //    }
    //    return (value - m_y0) / (m_delta) + m_x0;
    //}
private:
    float m_x0, m_y0;//, m_y1;
    float m_delta;
};



class Function2D : public Object {
public:
    virtual float operator()(float x, float y) = 0;
    virtual float invY (float x, float z) {
        throw;
    }
    virtual ~Function2D() = default;
};

class Constant2D : public Function2D {
public:
    Constant2D(float value) : m_value{value} {}
    Constant2D(const ITab& t);
    float operator()(float, float) override {
        return m_value;
    }
private:
    float m_value;
};

class Linear2Dx : public Function2D {
public:
    Linear2Dx(float x0, float value0, float x1, float value1) : m_x0{x0}, m_value0{value0}, m_delta{(value1-value0)/(x1-x0)} {}
    Linear2Dx(const ITab&);

    float operator()(float x, float y) override {
        return m_value0 + (x - m_x0) * m_delta;
    }
    
private:
    float m_x0;
    float m_value0;
    float m_delta;
};

class Linear2Dy : public Function2D {
public:
    Linear2Dy(float y0, float value0, float y1, float value1) : m_y0{y0}, m_value0{value0}, m_delta{(value1-value0)/(y1-y0)} {}
    Linear2Dy(const ITab&);
    float operator()(float x, float y) override {
        return m_value0 + (y - m_y0) * m_delta;
    }
    float invY(float x, float z) override {
        return (z - m_value0) / m_delta + m_y0;
    }
private:
    float m_y0;
    float m_value0;
    float m_delta;
};


class PatchwiseLinear2D : public Function2D {
public:
    PatchwiseLinear2D() {}
    PatchwiseLinear2D (const ITab&);

    float operator() (float x, float y) override;
    void AddFunction (glm::vec4, std::shared_ptr<Function2D>);
private:
    std::vector<glm::vec4> m_domains;
    std::vector<bool> m_varX;
    std::vector<std::shared_ptr<Function2D>> m_functions;
};


