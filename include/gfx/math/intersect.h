#pragma once

#include "gfx/math/line.h"
#include "gfx/math/rect.h"
#include "gfx/math/poly.h"
#include "gfx/math/polyline.h"
#include "gfx/math/circle.h"
#include "gfx/math/compound.h"

#include <typeinfo>
#include <typeindex>
#include <functional>
#include <unordered_map>
#include "gfx/math/collisionreport.h"
#include "gfx/hashpair.h"


class IntersectionFunction {
public:
    virtual CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) = 0;
};



class Intersector {
public:
    Intersector();
    CollisionReport Intersect(Shape* shape1, const glm::mat4& transform1, Shape* shape2, const glm::mat4& transform2);
private:
    std::unordered_map<std::pair<std::type_index, std::type_index>, std::shared_ptr<IntersectionFunction>> m_func;

};


class ConvexPolygonIntersectionFunction : public IntersectionFunction{
    CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
};

class ConvexCirclePolygonIntersectionFunction : public IntersectionFunction{
    CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
};

class CircleCircleIntersectionFunction : public IntersectionFunction{
    CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
};

class CompoundIntersectionFunction : public IntersectionFunction{
public:
    CompoundIntersectionFunction(Intersector* intersector) : m_intersector(intersector) {}
    CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
private:
    Intersector* m_intersector;
};




CollisionReport LineVsLine(Line*, Line*, glm::mat4&, glm::mat4&);
