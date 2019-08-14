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
    
    glm::vec3 min;
    glm::vec3 max;
    
    glm::vec3 GetSize() const;
    glm::vec3 GetCenter();
    glm::vec3 GetExtents();

    bool isVoid ();
    void Expand(float);
    void ExpandWith(const Bounds&);
    bool Contains(glm::vec3 P);
    bool Intersects(Bounds& other) const;
    bool Intersects2D(Bounds& other) const;

    // rotate a bounding box
    void Transform(const glm::mat4&);
    //void TransformXZ (const glm::mat4&);
};

inline bool Bounds::isVoid() {
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


//struct Bounds3D {
//    glm::vec3 min;
//    glm::vec3 max;
//    glm::vec3 GetExtents() {
//        return max - min;
//    }
//    //Bounds3D Apply(Transform&);
//};


#endif /* bounds_h */
