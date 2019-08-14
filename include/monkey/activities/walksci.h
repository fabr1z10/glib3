#pragma once

#include <gfx/activities/sequence.h>
#include <glm/glm.hpp>
#include <gfx/math/shape.h>
#include <string>
#include <unordered_map>
#include <gfx/math/geom.h>
#include <iostream>
class WalkSci : public Sequence {
public:
    WalkSci (int actor, glm::vec2 p) : Sequence(), m_actorId{actor}, m_p{p} {}
    ~WalkSci() override { std::cerr << "clearing walk...\n"; }
    WalkSci (const std::string& tag, glm::vec2 p) : Sequence(), m_tag{tag}, m_actorId(-1), m_p{p} {}
    void Start() override;
    void SetComplete() override;
private:
    Shape* m_shape;
    int m_actorId;
    std::string m_tag;
    glm::vec2 m_p;
};
