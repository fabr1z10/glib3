#pragma once

#include <monkey/math/shapes/line.h>
#include <monkey/math/shapes/rect.h>
#include <monkey/math/shapes/poly.h>
#include <monkey/math/shapes/polyline.h>
#include <monkey/math/shapes/circle.h>
#include <monkey/math/shapes/compound.h>

#include <typeinfo>
#include <typeindex>
#include <functional>
#include <unordered_map>
#include <monkey/math/collisionreport.h>
#include <monkey/hashpair.h>


//class IntersectionFunction {
//public:
//    virtual CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) = 0;
//    virtual ~IntersectionFunction() = default;
//};


class IIntersector {
public:
    virtual CollisionReport intersect(IShape*, IShape*, const glm::mat4&, const glm::mat4&) = 0;
};



template <typename T1, typename T2, CollisionReport(*f)(const T1&, const T2&, const glm::mat4&, const glm::mat4&)>
class Intersector : public IIntersector {
public:
    CollisionReport intersect(IShape* s1, IShape* s2, const glm::mat4& t1, const glm::mat4& t2) override {
        T1* sc1 = static_cast<T1*>(s1);
        T2* sc2 = static_cast<T2*>(s2);
        return f(*sc1, *sc2, t1, t2);

    }
};

class CompoundIntersector : public IIntersector {
public:
	CompoundIntersector(IIntersector* main) : m_main(main) {}
	CollisionReport intersect(IShape* s1, IShape* s2, const glm::mat4& t1, const glm::mat4& t2) override {
		CompoundShape* c2= static_cast<CompoundShape*>(s2);
		for (const auto& shape : c2->getShapes()) {
			auto report = m_main->intersect(s1, shape.get(), t1, t2);
			if (report.collide) {
				return report;
			}
		}
		return CollisionReport();
	}
private:
	IIntersector* m_main;
};

class AABB2DIntersector : public IIntersector {
public:
	CollisionReport intersect(IShape* s1, IShape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
};

class AABB3DIntersector : public IIntersector {
public:
	CollisionReport intersect(IShape* s1, IShape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
};

class Intersector2D : public IIntersector {
public:
    Intersector2D();
    CollisionReport intersect(IShape* shape1, IShape* shape2, const glm::mat4&, const glm::mat4&) override;
private:
    std::unordered_map<std::pair<ShapeType, ShapeType>, std::unique_ptr<IIntersector> > m_func;
};


class Intersector3D : public IIntersector {
public:
	Intersector3D();
	CollisionReport intersect(IShape* shape1, IShape* shape2, const glm::mat4&, const glm::mat4&) override;
private:
	std::unordered_map<std::pair<ShapeType, ShapeType>, std::unique_ptr<IIntersector> > m_func;
};

//
//
//class ConvexPolygonIntersectionFunction : public IntersectionFunction{
//    CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
//};
//
//class ConvexCirclePolygonIntersectionFunction : public IntersectionFunction{
//    CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
//};
//
//class CircleCircleIntersectionFunction : public IntersectionFunction{
//    CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
//};
//
//class CompoundIntersectionFunction : public IntersectionFunction{
//public:
//    CompoundIntersectionFunction(Intersector* intersector) : m_intersector(intersector) {}
//    CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
//private:
//    Intersector* m_intersector;
//};
//
//class BoxVsBox : public IntersectionFunction{
//    CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
//};
//
//class MultiSAT : public IntersectionFunction{
//    CollisionReport operator() (Shape* s1, Shape* s2, const glm::mat4& t1, const glm::mat4& t2) override;
//};
//
//CollisionReport LineVsLine(Line*, Line*, glm::mat4&, glm::mat4&);
