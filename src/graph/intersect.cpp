#include "graph/intersect.h"
#include "gfx/collider.h"
#include <iostream>

Intersector::Intersector() {
    //m_func[std::make_pair(std::type_index(typeid(Rect)), std::type_index(typeid(Rect)))] = h;
   

}

CollisionReport Intersector::Intersect(Shape * s1, const glm::mat4& t1, Shape *s2, const glm::mat4& t2) {

    auto it = m_func.find (std::make_pair(std::type_index(typeid(*s1)), std::type_index(typeid(*s2))));
    if (it == m_func.end()) {
        std::cout << "Don't have a routine to intersect shapes\n";
    } else {
        
    }
    return CollisionReport();
}

CollisionReport ConvexPolygonIntersectionFunction::operator()(Shape *s1, Shape *s2, const glm::mat4 &t1, const glm::mat4 &t2)
{
    // in order to perform a collision test between two convex shapes, we will leverage the SAT
    // (ie Separating Axis Theorem).
}
