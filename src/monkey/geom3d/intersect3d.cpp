#include <monkey/geom3d/intersect3d.hpp>

using namespace geom3d;

Intersector3D::Intersector3D() {

    m_func[std::make_pair(Shape3DType::SEGMENT, Shape3DType::PLANE)] =
            std::make_unique<TIntersectionFunction<Segment, Plane, intersectSegmentPlane>>();
    m_func[std::make_pair(Shape3DType::PLANE, Shape3DType::PLANE)] =
            std::make_unique<TIntersectionFunction<Plane, Plane, intersectPlanes>>();
    m_func[std::make_pair(Shape3DType::SEGMENT, Shape3DType::AABB)] =
            std::make_unique<TIntersectionFunction<Segment, AABox, intersectSegmentAABB>>();
    m_func[std::make_pair(Shape3DType::AABB, Shape3DType::PLANE)] =
            std::make_unique<TIntersectionFunction<AABox, Plane, TestAABBPlane>>();
    m_func[std::make_pair(Shape3DType::AABB, Shape3DType::AABB)] =
            std::make_unique<TIntersectionFunction<AABox, AABox, TestAABBAABB>>();
}

CollisionReport Intersector3D::intersect(Shape3D * s1, const glm::mat4& t1, Shape3D *s2, const glm::mat4& t2) {

//    auto it = m_func.find (std::make_pair(s1->getType(), s2->getType()));
//    if (it == m_func.end()) {
//        it = m_func.find (std::make_pair(std::type_index(typeid(*s2)), std::type_index(typeid(*s1))));
//        if (it == m_func.end()) {
//            std::cout << "Don't have a routine to intersect shapes\n";
//        } else {
//            auto report = it->second->operator()(s2, s1, t2, t1);
//            report.direction *= -1.0f;
//            return report;
//        }
//
//    } else {
//        return it->second->operator()(s1,s2,t1,t2);
//    }
//    return CollisionReport();
}
