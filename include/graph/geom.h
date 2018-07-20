#pragma once

#include "glm/glm.hpp"

class Poly;

const float epsilon = 0.0001f;

struct LineSegment {
    glm::vec2 A;
    glm::vec2 B;
};

template <class T>
bool isEqual (T x, T y, T eps = epsilon) {
    return std::abs(x-y) < eps;
}

template <class T>
bool isZero (T x, T eps = epsilon) {
    return isEqual(x, 0.0f, eps);
}

inline float cross (glm::vec2 a, glm::vec2 b) {
    return a.x * b.y - a.y * b.x;
}

inline float distSq (glm::vec2& a, glm::vec2& b) {
    float p = (a.x - b.x);
    float q = (a.y - b.y);
    return p*p + q*q;
}

template <class T>
T Clamp(T x, T m, T M) {
    return (x > M ? M : (x < m ? m : x));
}

// rotate ccw vector P by 90 deg
inline glm::vec2 Perp(glm::vec2 P) {
    return glm::vec2(-P.y, P.x);
}

// tests whether P is between A and B
bool IsBetween (glm::vec2 A, glm::vec2 B, glm::vec2 P, float eps = 0.01f);

float DistFromSegment (glm::vec2 A, glm::vec2 B, glm::vec2 P);
bool LineSegmentCross (glm::vec2, glm::vec2, glm::vec2, glm::vec2);
float LineSegmentIntersection (glm::vec2, glm::vec2, glm::vec2, glm::vec2);
bool inLineOfSight (const Poly&, glm::vec2, glm::vec2);
//void FindPathInPoly (const Poly&, glm::vec2 Start, glm::vec2 End);
