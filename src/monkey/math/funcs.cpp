#include <monkey/math/funcs.h>
#include <monkey/lua/luatable.h>
#include <monkey/engine.h>
#include <monkey/scenefactory.h>


PatchwiseLinear2D::PatchwiseLinear2D(const LuaTable& t) {
    luabridge::LuaRef quads = t.Get<luabridge::LuaRef>("rects");
    auto factory = Engine::get().GetSceneFactory();
    for (int i = 0; i < quads.length(); ++i) {
        luabridge::LuaRef f = quads[i + 1];
        LuaTable funcTable(f);
        glm::vec2 pos = funcTable.Get<glm::vec2>("pos");
        glm::vec2 size = funcTable.Get<glm::vec2>("size");
        glm::vec4 domain (pos.x, pos.y, pos.x+size.x, pos.y +size.y);
        auto fref = funcTable.Get<luabridge::LuaRef>("func");
        LuaTable ft(fref);
        auto func = factory->make<Function2D>(ft);
        AddFunction(domain, func);
    }
}

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

Linear2Dy::Linear2Dy(const ITable & t) : Function2D() {
    auto values = t.get<glm::vec4>("values");
    m_y0 = values[0];
    m_value0 = values[1];
    m_delta = (values[3] - values[1]) / (values[2] - values[0]);
}


Constant2D::Constant2D(const LuaTable & t) : Function2D() {
    m_value = t.Get<float>("value");
}