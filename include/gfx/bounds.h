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
    
    glm::vec2 min;
    glm::vec2 max;
    
    glm::vec2 GetSize();
    glm::vec2 GetCenter();
    glm::vec2 GetExtents();
    
    void Expand(float);
    bool Contains(glm::vec2 P);
    bool Intersects(Bounds& other) const;
    // rotate a bounding box
    void Transform(const glm::mat4&);
};

inline bool Bounds::Intersects(Bounds& other) const {
    return !(other.min.x >= max.x || other.max.x <= min.x || other.min.y >= max.y || other.max.y <= min.y);
}

inline glm::vec2 Bounds::GetSize() {
    return glm::vec2(max.x - min.x, max.y - min.y);
}

inline glm::vec2 Bounds::GetCenter() {
    return 0.5f * (min + max);
}

inline glm::vec2 Bounds::GetExtents() {
    return 0.5f * GetSize();
}


struct Bounds3D {
    glm::vec3 min;
    glm::vec3 max;
    glm::vec3 GetExtents() {
        return max - min;
    }
    //Bounds3D Apply(Transform&);
};


#endif /* bounds_h */
