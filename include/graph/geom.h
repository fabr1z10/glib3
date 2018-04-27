#include "glm/glm.hpp"

inline float cross (glm::vec2& a, glm::vec2& b) {
    return a.x * b.y - a.y * b.x;
}