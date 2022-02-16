#include <monkey/math/intersect.h>
#include <monkey/components/collider.h>
#include <iostream>
#include <monkey/math/geomalgo.h>
//#include <monkey/math/triangle.h>
#include <monkey/math/shapes/polytri.h>
#include <monkey/math/algo/sat.h>
#include <monkey/math/algo/geometry.h>
#include <monkey/math/shapes3d/pseudo3d.h>


CollisionReport AABB2DIntersector::intersect(IShape *s1, IShape *s2, const glm::mat4 &t1, const glm::mat4 &t2) {
	CollisionReport report;
	auto b1 = s1->getBounds();
	b1.Transform(t1);
	auto b2 = s2->getBounds();
	b2.Transform(t2);
	report.collide = b1.Intersects2D(b2);
	return report;
}

CollisionReport AABBToConvex::intersect(IShape *s1, IShape *s2, const glm::mat4 &t1, const glm::mat4 &t2) {
    auto bounds = s1->getBounds();
    bounds.Transform(t1);
    auto* sc2 = static_cast<IConvexPolygon*>(s2);
    auto r = Rect(bounds.max.x - bounds.min.x, bounds.max.y - bounds.min.y, glm::vec3(bounds.min.x, bounds.min.y, 0.0f));
    return SAT(r, *sc2, glm::mat4(1.0f), t2);
}

CollisionReport AABB3DIntersector::intersect(IShape *s1, IShape *s2, const glm::mat4 &t1, const glm::mat4 &t2) {
	CollisionReport report;
	auto b1 = s1->getBounds();
	b1.Transform(t1);
	auto b2 = s2->getBounds();
	b2.Transform(t2);
	report.collide = b1.Intersects(b2);
	return report;

}

CollisionReport AABBvsPseudo3D::intersect(IShape *s1, IShape *s2, const glm::mat4 &t1, const glm::mat4 &t2) {
    // test z first
    auto aabbBounds = s1->getBounds();
    aabbBounds.Transform(t1);
    auto pseudo = dynamic_cast<Pseudo3DShape*>(s2);
    auto dz = pseudo->getHalfDepth();
    float z = t2[3][2];
    bool not_overlap = (aabbBounds.min.z > z + dz) || (z - dz > aabbBounds.max.z);
    if (not_overlap) {
        return CollisionReport();
    }
    return m_intersector->intersect(s1, pseudo->getInternalShape(), t1, t2);
}

Intersector3D::Intersector3D() {
    m_int2D = std::make_shared<Intersector2D>();
	m_func[std::make_pair(ShapeType::AABB, ShapeType::AABB)] =
			std::make_unique<AABB3DIntersector>();
	m_func[std::make_pair(ShapeType::AABB, ShapeType::COMPOUND)] =
			std::make_unique<CompoundIntersector>(this);
    m_func[std::make_pair(ShapeType::COMPOUND, ShapeType::COMPOUND)] =
            std::make_unique<CompoundIntersector>(this);
    //m_func[std::make_pair(ShapeType::PSEUDO3D, ShapeType::PSEUDO3D)] =
    //        std::make_unique<CompoundIntersector>(this);
    m_func[std::make_pair(ShapeType::PSEUDO3D, ShapeType::COMPOUND)] =
            std::make_unique<CompoundIntersector>(this);
    m_func[std::make_pair(ShapeType::AABB, ShapeType::PSEUDO3D)] =
            std::make_unique<AABBvsPseudo3D>(m_int2D.get());
}

Intersector2D::Intersector2D() {

    m_func[std::make_pair(ShapeType::SEGMENT, ShapeType::SEGMENT)] =
            std::make_unique<Intersector<IConvexPolygon, IConvexPolygon, SAT>>();
    m_func[std::make_pair(ShapeType::SEGMENT, ShapeType::RECT)] =
            std::make_unique<Intersector<IConvexPolygon, IConvexPolygon, SAT>>();
    m_func[std::make_pair(ShapeType::RECT, ShapeType::RECT)] =
            std::make_unique<Intersector<IConvexPolygon, IConvexPolygon, SAT>>();


    m_func[std::make_pair(ShapeType::SEGMENT, ShapeType::CONVEXPOLY)] =
            std::make_unique<Intersector<IConvexPolygon, IConvexPolygon, SAT>>();
    m_func[std::make_pair(ShapeType::RECT, ShapeType::CONVEXPOLY)] =
            std::make_unique<Intersector<IConvexPolygon, IConvexPolygon, SAT>>();
    m_func[std::make_pair(ShapeType::CONVEXPOLY, ShapeType::CONVEXPOLY)] =
            std::make_unique<Intersector<IConvexPolygon, IConvexPolygon, SAT>>();

    m_func[std::make_pair(ShapeType::SEGMENT, ShapeType::CIRCLE)] =
            std::make_unique<Intersector<IConvexPolygon, Circle, SATCircle>>();
    m_func[std::make_pair(ShapeType::RECT, ShapeType::CIRCLE)] =
            std::make_unique<Intersector<IConvexPolygon, Circle, SATCircle>>();
    m_func[std::make_pair(ShapeType::CONVEXPOLY, ShapeType::CIRCLE)] =
            std::make_unique<Intersector<IConvexPolygon, Circle, SATCircle>>();

    m_func[std::make_pair(ShapeType::CIRCLE, ShapeType::CIRCLE)] =
            std::make_unique<Intersector<Circle, Circle, circleVsCircle>>();

	m_func[std::make_pair(ShapeType::RECT, ShapeType::COMPOUND)] =
			std::make_unique<CompoundIntersector>(this);
	m_func[std::make_pair(ShapeType::AABB, ShapeType::COMPOUND)] =
			std::make_unique<CompoundIntersector>(this);
	m_func[std::make_pair(ShapeType::AABB, ShapeType::AABB)] =
			std::make_unique<AABB2DIntersector>();
    m_func[std::make_pair(ShapeType::AABB, ShapeType::CONVEXPOLY)] =
            std::make_unique<AABBToConvex>();

}

CollisionReport Intersector2D::intersect(IShape * s1, IShape *s2, const glm::mat4& t1, const glm::mat4& t2) {

	if (s1 == nullptr || s2 == nullptr) {
		return CollisionReport();
	}
    auto it = m_func.find (std::make_pair(s1->getShapeType(), s2->getShapeType()));
    if (it == m_func.end()) {
        it = m_func.find (std::make_pair(s2->getShapeType(), s1->getShapeType()));
        if (it == m_func.end()) {
            std::cout << "Don't have a routine to intersect shapes\n";
        } else {
            auto report = it->second->intersect(s2, s1, t2, t1);
            report.direction *= -1.0f;
            return report;
        }
        
    } else {
        return it->second->intersect(s1, s2, t1, t2);
    }
    return CollisionReport();
}
CollisionReport Intersector3D::intersect(IShape * s1, IShape *s2, const glm::mat4& t1, const glm::mat4& t2) {

	if (s1 == nullptr || s2 == nullptr) {
		return CollisionReport();
	}
	auto it = m_func.find (std::make_pair(s1->getShapeType(), s2->getShapeType()));
	if (it == m_func.end()) {
		it = m_func.find (std::make_pair(s2->getShapeType(), s1->getShapeType()));
		if (it == m_func.end()) {
			std::cout << "Don't have a routine to intersect shapes\n";
		} else {
			auto report = it->second->intersect(s2, s1, t2, t1);
			report.direction *= -1.0f;
			return report;
		}

	} else {
		return it->second->intersect(s1, s2, t1, t2);
	}
	return CollisionReport();
}
//CollisionReport ConvexPolygonIntersectionFunction::operator()(Shape *s1, Shape *s2, const glm::mat4 &t1, const glm::mat4 &t2)
//{
//    // in order to perform a collision test between two convex shapes, we will leverage the SAT
//    // (ie Separating Axis Theorem).
//    // We need first to get the axes. For convex polygons the axes to test are the normal to the edges
//
//    auto edges1 = s1->getEdges();
//    auto edges2 = s2->getEdges();
//
//    std::unordered_set<glm::vec2> axes;
//    for (auto& e : edges1) {
//
//        axes.insert (glm::normalize(glm::vec2(t1 * glm::vec4(-e.y, e.x, 0.0f, 0.0f))));
//    }
//    for (auto& e : edges2) {
//        axes.insert (glm::normalize(glm::vec2(t2 * glm::vec4(-e.y, e.x, 0.0f, 0.0f))));
//    }
//    return SAT(axes, s1,s2, t1,t2);
//}
//
//CollisionReport ConvexCirclePolygonIntersectionFunction::operator()(Shape *s1, Shape *s2, const glm::mat4 &t1, const glm::mat4 &t2)
//{
//    // it works exactly as ConvexPolygonIntersectionFunction but it adds another axis, which is the
//
//    auto edges1 = s1->getEdges();
//    auto edges2 = s2->getEdges();
//
//    std::unordered_set<glm::vec2> axes;
//    for (auto& e : edges1) {
//
//        axes.insert (glm::normalize(glm::vec2(t1 * glm::vec4(-e.y, e.x, 0.0f, 0.0f))));
//    }
//    for (auto& e : edges2) {
//        axes.insert (glm::normalize(glm::vec2(t2 * glm::vec4(-e.y, e.x, 0.0f, 0.0f))));
//    }
//
//    // loop through all points
//    glm::vec2 center = glm::vec2(t1 * glm::vec4(s1->getPoints()[0], 0.0f, 1.0f));
//    auto vertices = s2->getPoints();
//    glm::vec2 extraAxis(0.0f);
//    float mind2 = std::numeric_limits<float>::infinity();
//    for (auto& p : vertices) {
//        glm::vec2 pw = glm::vec2(t2 * glm::vec4(p, 0.0f, 1.0f));
//        glm::vec2 d = center - pw;
//        float d2 = d.x*d.x +d.y*d.y;
//        if (d2 <= mind2) {
//            mind2 = d2;
//            extraAxis = d;
//        }
//    }
//    axes.insert (glm::normalize(extraAxis));
//
//
//
//    return SAT(axes, s1,s2, t1,t2);
//}
//
//CollisionReport CircleCircleIntersectionFunction::operator()(Shape *s1, Shape *s2, const glm::mat4 &t1,
//                                                                             const glm::mat4 &t2)
//{
//    glm::vec2 c1 = glm::vec2(t1 * glm::vec4(s1->getPoints()[0], 0.0f, 1.0f));
//    glm::vec2 c2 = glm::vec2(t2 * glm::vec4(s2->getPoints()[0], 0.0f, 1.0f));
//    std::unordered_set<glm::vec2> axes;
//    axes.insert (glm::normalize(c2-c1));
//    return SAT(axes, s1, s2, t1,t2);
//
//}
//
//CollisionReport CompoundIntersectionFunction::operator()(Shape *s1, Shape *s2, const glm::mat4 &t1,
//                                                             const glm::mat4 &t2)
//{
//    // the first element is a compound. Run a intersection for every shape in it
//    CompoundShape* cs = static_cast<CompoundShape*>(s1);
//    const auto& shapes = cs->GetShapes();
//    for (auto& s : shapes) {
//        CollisionReport report = m_intersector->Intersect(s.get(), t1, s2, t2);
//        if (report.collide)
//            return report;
//    }
//    return CollisionReport();
//}
//
//CollisionReport BoxVsBox::operator()(Shape *s1, Shape *s2, const glm::mat4 &t1, const glm::mat4 &t2) {
//    CollisionReport report;
//    report.collide =true;
//    return report;
//}
//
//// this is used for checking collision between a tessellated polygon and a convex shape
//// like rect, line, or convex poly. There's a different routine for tessellated vs circle
//// and tessellated vs tessellated
//CollisionReport MultiSAT::operator()(Shape *s1, Shape *s2, const glm::mat4 &t1, const glm::mat4 &t2) {
//    // the first element is a tessellated polygon.
//    // Run a intersection for every triangle in it
//    PolyTri* cs = static_cast<PolyTri*>(s1);
//    auto e1 = s1->getEdges();
//    auto e2 = s2->getEdges();
//    int ntri = e1.size() / 3;
//    std::vector<glm::vec2> s2edges;
//    for (auto& e : e2) {
//        s2edges.push_back(glm::normalize(glm::vec2(t2 * glm::vec4(-e.y, e.x, 0.0f, 0.0f))));
//    }
//    for (int i = 0; i < ntri; ++i) {
//        int k = 3 * i;
//        std::unordered_set<glm::vec2> axes;
//        axes.insert (glm::normalize(glm::vec2(t1 * glm::vec4(-e1[k].y, e1[k].x, 0.0f, 0.0f))));
//        axes.insert (glm::normalize(glm::vec2(t1 * glm::vec4(-e1[k+1].y, e1[k+1].x, 0.0f, 0.0f))));
//        axes.insert (glm::normalize(glm::vec2(t1 * glm::vec4(-e1[k+2].y, e1[k+2].x, 0.0f, 0.0f))));
//        // now add edges of other shape
//        for (const auto& s2e : s2edges)
//            axes.insert(s2e);
//        auto report = SAT(axes, s1, s2, t1,t2);
//        if (report.collide)
//            return report;
//    }
//    return CollisionReport();
//
//}
