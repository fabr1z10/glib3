//
//  bounds.h
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#ifndef bounds_h
#define bounds_h


#include <glm/glm.hpp>

// An axis-aligned bounding box (AABB)
struct Bounds {
    Bounds() : min(0.0f), max(0.0f) {}
    Bounds(const glm::vec3& min, const glm::vec3& max) : min(min), max(max) {}
    glm::vec3 min;
    glm::vec3 max;
    
    glm::vec3 GetSize() const;
    glm::vec3 GetCenter();
    glm::vec3 GetExtents();

    bool isVoid () const;
    void Expand(float);
    void ExpandWith(const Bounds&);
    bool Contains(glm::vec3 P);
    bool Intersects(Bounds& other) const;
    bool Intersects2D(Bounds& other) const;

    // rotate a bounding box
    void Translate (const glm::vec3&);
    void Transform(const glm::mat4&);
    //void TransformXZ (const glm::mat4&);
};

inline bool Bounds::isVoid() const {
    return (max.x == min.x && max.y == min.y && max.z == min.z);

}
inline bool Bounds::Intersects(Bounds& other) const {
    return !(other.min.x > max.x || other.max.x < min.x ||
        other.min.y > max.y || other.max.y < min.y ||
        other.min.z > max.z || other.max.z < min.z);
}
inline bool Bounds::Intersects2D(Bounds& other) const {
    return !(other.min.x > max.x || other.max.x < min.x ||
             other.min.y > max.y || other.max.y < min.y);
}
inline glm::vec3 Bounds::GetSize() const {
    return glm::vec3(max.x - min.x, max.y - min.y, max.z - min.z);
}

inline glm::vec3 Bounds::GetCenter() {
    return 0.5f * (min + max);
}

inline glm::vec3 Bounds::GetExtents() {
    return 0.5f * GetSize();
}



#endif /* bounds_h */
