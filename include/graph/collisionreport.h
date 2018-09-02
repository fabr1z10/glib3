#pragma once
#include <glm/glm.hpp>

struct CollisionReport {
    CollisionReport()
    : collide(false) {}
    bool collide;
    float distance;
    glm::vec2 direction;
    
};
