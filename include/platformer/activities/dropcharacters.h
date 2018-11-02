#pragma once

#include <gfx/activity.h>
#include <glm/glm.hpp>


class DropCharacters : public Activity {
public:
    DropCharacters(const std::string& actorId, glm::vec2 pos);
    void Start() override;
    void Run (float dt) override  {}
private:
    glm::vec2 m_pos;
    std::string m_animId;
    std::string m_actorId;
};
