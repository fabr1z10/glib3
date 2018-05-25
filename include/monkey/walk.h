#pragma once

#include <gfx/sequence.h>
#include <glm/glm.hpp>
#include <graph/shape.h>

class Walk : public Sequence {
public:
    Walk (int id, const std::string& actor, glm::vec2 p, Shape* shape) : Sequence(id), m_actorId{actor}, m_p{p}, m_shape{shape} {}
    void Start() override;

private:
    Shape* m_shape;
    std::string m_actorId;
    glm::vec2 m_p;
};