#include <monkey/math/funcs.h>
#include <monkey/lua/luatable.h>

float PatchwiseLinear2D::operator() (float x, float y) {
    int i{0};
    for (auto& d : m_domains) {
        if (!(x < d[0] || x > d[2] || y < d[1] || y > d[3])) {
            return m_functions[i]->operator()(x, y);
        }
        // found the right patch
        ++i;
    }
    return 0.0f;
}

void PatchwiseLinear2D::AddFunction (glm::vec4 domain , std::shared_ptr<Function2D> f) {
    m_domains.push_back(domain);
    m_functions.push_back(std::move(f));
}

Linear2Dy::Linear2Dy(const LuaTable & t) : Function2D() {
    auto values = t.Get<glm::vec4>("values");
    m_y0 = values[0];
    m_value0 = values[1];
    m_delta = (values[3] - values[1]) / (values[2] - values[0]);
}

Constant2D::Constant2D(const LuaTable & t) : Function2D() {
    m_value = t.Get<float>("value");
}