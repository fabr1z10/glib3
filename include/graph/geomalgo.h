#pragma once

#include "graph/collisionreport.h"
#include <vector>

class Shape;

CollisionReport SegmentTest(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D);
CollisionReport SAT(std::vector<glm::vec2>& axesw, Shape* a, Shape* b, const glm::mat4& ta, const glm::mat4& tb);
glm::vec2 Projection (const std::vector<glm::vec2>&, const glm::vec2& axis, const glm::mat4& t);
