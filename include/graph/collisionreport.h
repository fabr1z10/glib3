#pragma once

#include <glm/glm.hpp>

class Entity;

struct CollisionReport {
    CollisionReport()
    : collide(false) {}
    bool collide;
    float distance;
    glm::vec2 direction;
    
};

struct RayCastHit2D {
    RayCastHit2D() : collide(false), length(0.0f), entity(nullptr) {}
    RayCastHit2D(bool collide, float l, glm::vec2 normal) : collide(collide), length(l), entity(nullptr), normal(normal) {}
    bool collide;
    float length;
    Entity* entity;
    glm::vec2 normal;
};