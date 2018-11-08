#pragma once

#include "gfx/math/collisionreport.h"
#include <vector>
#include <unordered_set>

class Shape;

CollisionReport SegmentTest(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D);
CollisionReport SAT(std::unordered_set<glm::vec2>& axesw, Shape* a, Shape* b, const glm::mat4& ta, const glm::mat4& tb);
glm::vec2 Projection (const std::vector<glm::vec2>&, const glm::vec2& axis, const glm::mat4& t);
float ComputeOverlap(glm::vec2& p1, glm::vec2& p2);