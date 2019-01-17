#pragma once

#include <glm/glm.hpp>
#include <gfx/framechangehandler.h>
#include <unordered_map>
#include <vector>

struct ChildPosition {
    std::string name;
    glm::vec3 offset;
    float angle;
};


class RelativePosHandler : public IFrameChangeHandler {
public:
    virtual void Handle (const std::string& anim, int frame) override;
    virtual void Init(luabridge::LuaRef ref, const std::string& anim, int frame) override;
private:
    std::unordered_map<std::string, std::vector<ChildPosition>> m_childrenPos;
};