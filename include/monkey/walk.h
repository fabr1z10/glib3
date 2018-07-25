#pragma once

#include <gfx/sequence.h>
#include <glm/glm.hpp>
#include <graph/shape.h>
#include <string>
#include <unordered_map>
#include <graph/geom.h>

class Walk : public Sequence {
public:
    Walk (const std::string& actor, glm::vec2 p ) :
            Sequence(), m_actorId{actor}, m_p{p} {}
    void Start() override;
    void SetComplete() override;
private:
    Shape* m_shape;
    std::string m_actorId;
    glm::vec2 m_p;
};
