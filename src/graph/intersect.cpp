#include "graph/intersect.h"
#include "gfx/collider.h"
#include <iostream>
#include "graph/geomalgo.h"

Intersector::Intersector() {
    auto convexPolyIntersector = std::make_shared<ConvexPolygonIntersectionFunction>();
    m_func[std::make_pair(std::type_index(typeid(Rect)), std::type_index(typeid(Rect)))] = convexPolyIntersector;
    m_func[std::make_pair(std::type_index(typeid(Line)), std::type_index(typeid(Rect)))] = convexPolyIntersector;
   

}

CollisionReport Intersector::Intersect(Shape * s1, const glm::mat4& t1, Shape *s2, const glm::mat4& t2) {

    auto it = m_func.find (std::make_pair(std::type_index(typeid(*s1)), std::type_index(typeid(*s2))));
    if (it == m_func.end()) {
        it = m_func.find (std::make_pair(std::type_index(typeid(*s2)), std::type_index(typeid(*s1))));
        if (it == m_func.end()) {
            std::cout << "Don't have a routine to intersect shapes\n";
        } else {
            auto report = it->second->operator()(s2, s1, t2, t1);
            report.direction *= -1.0f;
            return report;
        }
        
    } else {
        return it->second->operator()(s1,s2,t1,t2);
    }
    return CollisionReport();
}

CollisionReport ConvexPolygonIntersectionFunction::operator()(Shape *s1, Shape *s2, const glm::mat4 &t1, const glm::mat4 &t2)
{
    // in order to perform a collision test between two convex shapes, we will leverage the SAT
    // (ie Separating Axis Theorem).
    // We need first to get the axes. For convex polygons the axes to test are the normal to the edges

    auto edges1 = s1->getEdges();
    auto edges2 = s2->getEdges();

    std::unordered_set<glm::vec2> axes;
    for (auto& e : edges1) {
        
        axes.insert (glm::normalize(glm::vec2(t1 * glm::vec4(-e.y, e.x, 0.0f, 0.0f))));
    }
    for (auto& e : edges2) {
        axes.insert (glm::normalize(glm::vec2(t2 * glm::vec4(-e.y, e.x, 0.0f, 0.0f))));
    }
    return SAT(axes, s1,s2, t1,t2);
}
