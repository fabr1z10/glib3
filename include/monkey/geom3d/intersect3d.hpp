#include <monkey/geom3d/algos.hpp>
#include <unordered_map>
#include <functional>
#include <monkey/hashpair.h>

// handles intersection of 3d shapes
class Intersector3D {
public:
    Intersector3D();
    geom3d::CollisionReport intersect(geom3d::Shape3D* shape1, const glm::mat4& transform1, geom3d::Shape3D* shape2, const glm::mat4& transform2);
private:
    std::unordered_map<std::pair<geom3d::Shape3DType, geom3d::Shape3DType>, std::unique_ptr<geom3d::IntersectionFunction> > m_func;

};
