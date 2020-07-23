#include <monkey/math/funcs.h>
#include <monkey/engine.h>
#include <monkey/scenefactory.h>


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


PatchwiseLinear2D::PatchwiseLinear2D(const ITable & t) {
    t.foreach<PyDict>("rect", [&] (const PyDict& table) {
        // read bottom left corner
        auto pos = table.get<glm::vec2>("pos");
        auto size = table.get<glm::vec2>("size");
        auto factory = Engine::get().GetSceneFactory();
        auto func = table.get<PyTable>("func");
        auto f = factory->make2<Function2D>(func);
        this->AddFunction(glm::vec4(pos[0], pos[1], pos[0]+size[0], pos[1]+size[1]), f);
    });

}

Linear2Dy::Linear2Dy(const ITable & t) : Function2D() {
    auto values = t.get<glm::vec4>("values");
    m_y0 = values[0];
    m_value0 = values[1];
    m_delta = (values[3] - values[1]) / (values[2] - values[0]);
}

Linear2Dx::Linear2Dx(const ITable & t) : Function2D() {
    auto values = t.get<glm::vec4>("values");
    m_x0 = values[0];
    m_value0 = values[1];
    m_delta = (values[3] - values[1]) / (values[2] - values[0]);
}

Constant2D::Constant2D(const ITable &t) {
    m_value = t.get<float>("value");
}