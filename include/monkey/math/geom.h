#pragma once

#define M_PI 3.14159265358979323846

#include "glm/glm.hpp"

class Poly;


namespace monkey {
    const glm::vec3 left = glm::vec3(-1, 0, 0);
    const glm::vec3 right = glm::vec3(1, 0, 0);
    const glm::vec3 down = glm::vec3(0, -1, 0);
    const glm::vec3 up = glm::vec3(0, 1, 0);
    const glm::vec3 front = glm::vec3(0, 0, 1);
    const glm::vec3 back = glm::vec3(0, 0, -1);
    /// ray intersection between P0 + d0 * u and P1 + d1*v
    float rayint (glm::vec2 P0, glm::vec2 d0, glm::vec2 P1, glm::vec2 d1);
	const float epsilon = 0.0001f;
}


const float deg2rad = M_PI / 180.0f;
const float rad2deg = 180.0f / M_PI;
//const glm::vec3 vec_down = glm::vec3(0, -1, 0);

struct LineSegment {
    glm::vec2 A;
    glm::vec2 B;
};

template <class T>
bool isEqual (T x, T y, T eps = monkey::epsilon) {
    return std::abs(x-y) < eps;
}

template <class T>
bool isZero (T x, T eps = monkey::epsilon) {
    return isEqual(x, 0.0f, eps);
}

inline bool match(glm::vec2 A, glm::vec2 B, float tol) {
    glm::vec2 c = B-A;
    return (c.x*c.x+c.y*c.y) < tol;
}


inline float cross (glm::vec2 a, glm::vec2 b) {
    return a.x * b.y - a.y * b.x;
}

inline float distSq (glm::vec2& a, glm::vec2& b) {
    float p = (a.x - b.x);
    float q = (a.y - b.y);
    return p*p + q*q;
}

inline float length2 (glm::vec2 P) {
    return P.x * P.x + P.y * P.y;
}

// returns the angle (in radians) between two vectors
inline float angle(glm::vec2 v1, glm::vec2 v2) {
    return std::acos(glm::dot(v1, v2));
}

inline int sign (float f) {
    return f>=0.0f ? 1 : -1;
}

inline float signf (float f) {
    return f >= 0.0f ? 1.0f : -1.0f;
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

float GetFirstSolution(float, float, float);
float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float deltaTime, float maxSpeed = 10000000.0f);