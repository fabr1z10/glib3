#include <gfx/components/relativepos.h>
#include <gfx/entity.h>
#include <sstream>
#include <gfx/lua/luatable.h>
#include <gfx/error.h>

void RelativePosHandler::Handle (const std::string& anim, int frame) {
    std::stringstream stream;
    stream << anim << "@" << frame;

    auto it = m_childrenPos.find(stream.str());
    if (it == m_childrenPos.end()) {
        it = m_childrenPos.find(anim);
        if (it == m_childrenPos.end())
            return;
    }
    for (auto& cp : it->second) {
        auto child =  m_entity->GetNamedChild(cp.name);
        if (child != nullptr)
            child->SetPosition(glm::vec3(cp.offset, 0.0f), cp.angle);
    }

}


void RelativePosHandler::Init(luabridge::LuaRef ref, const std::string& anim, int frame) {
    std::stringstream key;
    key << anim;
    if (frame != -1)
        key << "@" << frame;
    luabridge::LuaRef idata = ref["pos"];
    if (idata.isNil()) {
        GLIB_FAIL("Relative pos handler requires pos field in additional info");
    }
    std::vector<ChildPosition> positions;
    for (int i = 0; i < idata.length(); ++i) {
        luabridge::LuaRef pos = idata[i+1];
        LuaTable t(pos);
        ChildPosition p;
        p.name = t.Get<std::string>("name");
        p.offset = t.Get<glm::vec2>("offset");
        p.angle = t.Get<float>("angle", 0.0f);
        positions.emplace_back(p);
    }
    m_childrenPos.insert(std::make_pair(key.str(), positions));
}
