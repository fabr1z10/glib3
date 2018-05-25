#pragma once

#include <gfx/sequence.h>
#include <glm/glm.hpp>

class Walk : public Sequence {
public:
    Walk (int id, const std::string& actor, glm::vec2 p) : Sequence(id), m_actorId{actor}, m_p{p} {}
    void Start() override;

private:
    std::string m_actorId;
    glm::vec2 m_p;
};