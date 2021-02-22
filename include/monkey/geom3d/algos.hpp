#include "monkey/geom3d/shapes.hpp"

namespace geom3d {

    const float eps = 0.0001f;

    struct CollisionReport {
        CollisionReport() : collide(false) {}
        bool collide;
        glm::vec3 a;
        glm::vec3 b;
        float c;
    };


    CollisionReport intersectPlanes(const Plane& p1, const Plane& p2);
    CollisionReport intersectSegmentAABB(const Segment& s, const geom3d::AABox& a);
    CollisionReport TestAABBPlane(const AABox& b, const Plane& p);
    CollisionReport TestAABBAABB(const AABox& a, const AABox& b);

    class IntersectionFunction {
    public:
        virtual CollisionReport run(Shape3D*, Shape3D*) = 0;

    };

    template <typename T1, typename T2, CollisionReport(*f)(const T1&, const T2&)>
    class TIntersectionFunction : public IntersectionFunction {
    public:
        CollisionReport run(Shape3D* s1, Shape3D* s2) override {
            T1* t1 = static_cast<T1*>(s1);
            T2* t2 = static_cast<T2*>(s2);
            return f(*t1, *t2);

        }
    };


}