#pragma once

#include <glm/glm.hpp>

class Entity;
class ICollider;

struct CollisionReport {
    CollisionReport()
    : collide(false) {}
    bool collide;
    float distance;
    glm::vec2 direction;
    
};

struct RayCastHit {
    RayCastHit() : collide(false), length(std::numeric_limits<float>::infinity()), entity(nullptr), segmentIndex(-1) {}
    RayCastHit(bool collide, float l, glm::vec3 normal) : collide(collide), length(l), entity(nullptr), normal(normal), segmentIndex(-1) {}
    bool collide;
    float length;
    ICollider* entity;
    glm::vec3 normal;
    int segmentIndex;
};

struct ShapeCastHit {
    ShapeCastHit () : entity(nullptr) {}
    CollisionReport report;
    ICollider* entity;


};

