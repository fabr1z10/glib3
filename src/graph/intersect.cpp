#include "graph/intersect.h"
#include "gfx/components/collider.h"
#include <iostream>
#include "graph/geomalgo.h"

Intersector::Intersector() {
    auto convexPolyIntersector = std::make_shared<ConvexPolygonIntersectionFunction>();
    auto convexCirclePolyIntersector = std::make_shared<ConvexCirclePolygonIntersectionFunction>();
    auto circleCircleIntersector = std::make_shared<CircleCircleIntersectionFunction>();
    auto compoundIntersector = std::make_shared<CompoundIntersectionFunction>(this);

    // SAT
    m_func[std::make_pair(std::type_index(typeid(Rect)), std::type_index(typeid(Rect)))] = convexPolyIntersector;
    m_func[std::make_pair(std::type_index(typeid(Line)), std::type_index(typeid(Line)))] = convexPolyIntersector;
    m_func[std::make_pair(std::type_index(typeid(Polygon)), std::type_index(typeid(Polygon)))] = convexPolyIntersector;
    m_func[std::make_pair(std::type_index(typeid(Line)), std::type_index(typeid(Rect)))] = convexPolyIntersector;
    m_func[std::make_pair(std::type_index(typeid(Polygon)), std::type_index(typeid(Rect)))] = convexPolyIntersector;
    m_func[std::make_pair(std::type_index(typeid(Line)), std::type_index(typeid(Polygon)))] = convexPolyIntersector;

    // extended SAT for circle
    m_func[std::make_pair(std::type_index(typeid(Circle)), std::type_index(typeid(Rect)))] = convexCirclePolyIntersector;
    m_func[std::make_pair(std::type_index(typeid(Circle)), std::type_index(typeid(Line)))] = convexCirclePolyIntersector;
    m_func[std::make_pair(std::type_index(typeid(Circle)), std::type_index(typeid(Polygon)))] = convexCirclePolyIntersector;

    // circle vs circle
    m_func[std::make_pair(std::type_index(typeid(Circle)), std::type_index(typeid(Circle)))] = circleCircleIntersector;

    // compound vs others
    m_func[std::make_pair(std::type_index(typeid(CompoundShape)), std::type_index(typeid(Rect)))] = compoundIntersector;
    m_func[std::make_pair(std::type_index(typeid(CompoundShape)), std::type_index(typeid(Line)))] = compoundIntersector;
    m_func[std::make_pair(std::type_index(typeid(CompoundShape)), std::type_index(typeid(Polygon)))] = compoundIntersector;
    m_func[std::make_pair(std::type_index(typeid(CompoundShape)), std::type_index(typeid(Circle)))] = compoundIntersector;
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

CollisionReport ConvexCirclePolygonIntersectionFunction::operator()(Shape *s1, Shape *s2, const glm::mat4 &t1, const glm::mat4 &t2)
{
    // it works exactly as ConvexPolygonIntersectionFunction but it adds another axis, which is the

    auto edges1 = s1->getEdges();
    auto edges2 = s2->getEdges();

    std::unordered_set<glm::vec2> axes;
    for (auto& e : edges1) {

        axes.insert (glm::normalize(glm::vec2(t1 * glm::vec4(-e.y, e.x, 0.0f, 0.0f))));
    }
    for (auto& e : edges2) {
        axes.insert (glm::normalize(glm::vec2(t2 * glm::vec4(-e.y, e.x, 0.0f, 0.0f))));
    }

    // loop through all points
    glm::vec2 center = glm::vec2(t1 * glm::vec4(s1->getPoints()[0], 0.0f, 1.0f));
    auto vertices = s2->getPoints();
    glm::vec2 extraAxis(0.0f);
    float mind2 = std::numeric_limits<float>::infinity();
    for (auto& p : vertices) {
        glm::vec2 pw = glm::vec2(t2 * glm::vec4(p, 0.0f, 1.0f));
        glm::vec2 d = center - pw;
        float d2 = d.x*d.x +d.y*d.y;
        if (d2 <= mind2) {
            mind2 = d2;
            extraAxis = d;
        }
    }
    axes.insert (glm::normalize(extraAxis));



    return SAT(axes, s1,s2, t1,t2);
}

CollisionReport CircleCircleIntersectionFunction::operator()(Shape *s1, Shape *s2, const glm::mat4 &t1,
                                                                             const glm::mat4 &t2)
{
    glm::vec2 c1 = glm::vec2(t1 * glm::vec4(s1->getPoints()[0], 0.0f, 1.0f));
    glm::vec2 c2 = glm::vec2(t2 * glm::vec4(s2->getPoints()[0], 0.0f, 1.0f));
    std::unordered_set<glm::vec2> axes;
    axes.insert (glm::normalize(c2-c1));
    return SAT(axes, s1, s2, t1,t2);

}

CollisionReport CompoundIntersectionFunction::operator()(Shape *s1, Shape *s2, const glm::mat4 &t1,
                                                             const glm::mat4 &t2)
{
    // the first element is a compound. Run a intersection for every shape in it
    CompoundShape* cs = static_cast<CompoundShape*>(s1);
    const auto& shapes = cs->GetShapes();
    for (auto& s : shapes) {
        CollisionReport report = m_intersector->Intersect(s.get(), t1, s2, t2);
        if (report.collide)
            return report;
    }
    return CollisionReport();
}