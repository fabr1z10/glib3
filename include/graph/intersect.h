#pragma once

#include "graph/line.h"
#include "graph/rect.h"
#include "graph/poly.h"
#include "graph/polyline.h"
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <unordered_map>
#include "graph/collisionreport.h"
#include "gfx/hashpair.h"


class IntersectionFunction {
public:
    virtual CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) = 0;
};

class ConvexPolygonIntersectionFunction : public IntersectionFunction{
    CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
};

class Intersector {
public:
    Intersector();
    CollisionReport Intersect(Shape* shape1, const glm::mat4& transform1, Shape* shape2, const glm::mat4& transform2);
private:
    std::unordered_map<std::pair<std::type_index, std::type_index>, std::shared_ptr<IntersectionFunction>> m_func;

};



CollisionReport LineVsLine(Line*, Line*, glm::mat4&, glm::mat4&);
