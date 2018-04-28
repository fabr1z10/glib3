#include "glm/glm.hpp"

class Poly;

inline float cross (glm::vec2& a, glm::vec2& b) {
    return a.x * b.y - a.y * b.x;
}

inline float distSq (glm::vec2& a, glm::vec2& b) {
    float p = (a.x - b.x);
    float q = (a.y - b.y);
    return p*p + q*q;
}


void FindPathInPoly (const Poly&, glm::vec2 Start, glm::vec2 End);