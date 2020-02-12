#include <monkey/math/poly.h>
#include <monkey/math/geom.h>
#include <monkey/error.h>
#include <monkey/math/geomalgo.h>
#include <monkey/entity.h>
#include <monkey/lua/luatable.h>

Polygon::Polygon(const std::vector<glm::vec2> &p) : m_points{p} {
    m_bounds.min = glm::vec3(p[0], 0.0f);
    m_bounds.max = glm::vec3(p[0], 0.0f);
    for (int i = 1; i < p.size(); ++i) {
        m_bounds.min.x = std::min(m_bounds.min.x, p[i].x);
        m_bounds.min.y = std::min(m_bounds.min.y, p[i].y);
        m_bounds.max.x = std::max(m_bounds.max.x, p[i].x);
        m_bounds.max.y = std::max(m_bounds.max.y, p[i].y);
    }

}


bool Polygon::isVertexConcave(int i) const {
    int n = m_points.size();
    glm::vec2 next = m_points[(i+1) % n];
    glm::vec2 prev = m_points[i == 0 ? n-1 : i-1];
    glm::vec2 left = prev - m_points[i];
    glm::vec2 right = next - m_points[i];
    float x = cross(left, right);
    return x < 0;
}

bool Polygon::isPointInside(glm::vec3 point) const {
    int i, j;
    bool c = false;
    int nvert = m_points.size();
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((m_points[i].y > point.y) != (m_points[j].y > point.y)) &&
             (point.x < (m_points[j].x-m_points[i].x) * (point.y-m_points[i].y) / (m_points[j].y-m_points[i].y) + m_points[i].x) )
            c = !c;
    }
    return c;
}

bool Polygon::isInLineOfSight(glm::vec2 A, glm::vec2 B) {
    //if (!isPointInside(A) || !isPointInside(B))
     //   return false;
    // checks to see if there's any intersection with the edges
    glm::vec2 P0 = m_points.back();
    for (auto& P1 : m_points) {
        if (LineSegmentCross(A, B, P0, P1))
            return false;
        P0 = P1;
    }
    return true;
}

void Polygon::accept (AcyclicVisitor& v) {
    Visitor<Polygon>* v1 = dynamic_cast<Visitor<Polygon>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a polygon visitor");
}

std::vector<glm::vec2> Polygon::getPoints() {
    return m_points;
}

std::vector<glm::vec2> Polygon::getEdges() {
    std::vector<glm::vec2> edges;
    for (int i = 1; i < m_points.size(); ++i)
        edges.push_back(m_points[i] - m_points[i-1]);
    edges.push_back(m_points.front() - m_points.back());
    return edges;
}

std::list<Hole>::iterator Poly::addHole(glm::vec2 pos, std::shared_ptr<Polygon> poly) {
    m_holes.push_back(Hole(pos, poly));
    auto it = m_holes.end();
    it--;
    return it;
}

Poly::Poly(const LuaTable & t) : Shape(t) {

    std::vector<float> outline = t.GetVector<float>("outline");

    std::vector<glm::vec2> points;
    for (size_t i = 0; i < outline.size(); i = i + 2)
        points.push_back(glm::vec2(outline[i], outline[i + 1]));
    m_contour = std::make_unique<Polygon>(points);

    //  holes
    if (t.HasKey("holes")) {
        std::unique_ptr<Polygon> mainOutline(new Polygon(points));
        auto holes = t.Get<luabridge::LuaRef>("holes");
        for (int j = 0; j < holes.length(); ++j) {
            luabridge::LuaRef h = holes[j + 1];
            std::vector<float> holeOutline = ReadVector<float>(h);
            std::vector<glm::vec2> points;
            for (size_t i = 0; i < holeOutline.size(); i = i + 2)
                points.push_back(glm::vec2(holeOutline[i], holeOutline[i + 1]));
            addHole(glm::vec2(0.0f), std::make_shared<Polygon>(points));
        }
    }
}

bool Poly::isPointInside(glm::vec3 P) const {
    if (!m_contour->isPointInside(P))
        return false;
    for (const auto& hole : m_holes) {
        if (hole.isPointInside(P)) {
            return false;
        }
    }
    return true;
}

void Poly::accept (AcyclicVisitor& v) {
    Visitor<Poly>* v1 = dynamic_cast<Visitor<Poly>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a poly visitor");
}


Polygon* Poly::GetPolygon() {
    return m_contour.get();
}

glm::vec2 Polygon::getNormalAtEdge (int edgeIndex) {
    return glm::normalize(Perp(m_points[(edgeIndex+1) % m_points.size()] - m_points[edgeIndex]));
}

glm::vec2 Polygon::getNormalAtVertex (int i) {
    glm::vec2 a = getNormalAtEdge(i);
    glm::vec2 b = getNormalAtEdge((i-1 >= 0) ? (i-1) : m_points.size()-1);
    return (glm::normalize(0.5f*(a+b)));
    //return glm::normalize(Perp(m_points[(edgeIndex+1) % m_points.size()] - m_points[edgeIndex]));
}

glm::vec2 Polygon::project(const glm::vec2 axis, const glm::mat4& worldTransform) {
    return Projection(m_points, axis, worldTransform);
}

//const glm::mat4& Hole::getWorldTransform() const {
//    return m_entity->GetWorldTransform();
//}
Poly::Poly (std::unique_ptr<Polygon> p) {
    m_contour = std::move(p);
    m_bounds = m_contour->getBounds();
}


bool Poly::isInLineOfSight(glm::vec2 A, glm::vec2 B) {

    if (!m_contour->isInLineOfSight(A, B)) {
        return false;
    }
    for (const auto& hole : m_holes) {
        if (!hole.isInLineOfSight(A, B))
            return false;
    }
    return true;


//    for (auto& p : m_polygons) {
//        if (!p->isInLineOfSight(A, B))
//            return false;
//    }
//    return true;
}

std::string Poly::toString() const {
    return "Poly";
}

std::string Polygon::toString() const {
    return "Polygon";
}

std::vector<glm::vec2> Poly::getPoints() {
    return m_contour->getPoints();
}
std::vector<glm::vec2> Poly::getEdges() {
    return m_contour->getEdges();
}


glm::vec2 Poly::GetVertex(int i) const {
    return m_contour->GetVertex(i);
}

const std::list<Hole>& Poly::getHoles() const {
    return m_holes;
}


void Hole::setPosition(glm::vec2 pos) {
    position = pos;
}

bool Hole::isPointInside (glm::vec3 P) const {
    //glm::mat4 wt = m_entity->GetWorldTransform();
    glm::vec3 Plocal = P - glm::vec3(position,0.0f);

    bool inside = m_polygon->isPointInside(Plocal);
    //std::cerr << P.x << ", " << P.y << " is inside == " << inside<< " ... " << position.x << ", " << position.y << "\n";
    return inside;
}

glm::vec2 Hole::getVertex(int i) const {
    //const glm::mat4& t = m_entity->GetWorldTransform();
    return m_polygon->GetVertex(i);
}
glm::vec2 Hole::getNormalAtVertex(int i) const {

    return m_polygon->getNormalAtVertex(i);

}

bool Hole::isInLineOfSight(glm::vec2 &A, glm::vec2 &B) const{
    glm::vec2 lA = A - position;
    glm::vec2 lB = B - position;
    return m_polygon->isInLineOfSight(lA, lB);
}

//for (i in 0...vertices.length)
//{
//var newPoint:Vector = vertices[i];
//var newSqDist:Float = DistanceSquared(newPoint.x, newPoint.y, point.x, point.y);
//
//if (oldSqDist + newSqDist + 2.0 * Math.sqrt(oldSqDist * newSqDist) - DistanceSquared(newPoint.x, newPoint.y, oldPoint.x, oldPoint.y) < epsilon) {
//return toleranceOnOutside;
//}
//
//var left:Vector;
//var right:Vector;
//if (newPoint.x > oldPoint.x)
//{
//left = oldPoint;
//right = newPoint;
//}
//else
//{
//left = newPoint;
//right = oldPoint;
//}
//
//if (left.x < point.x && point.x <= right.x && (point.y - left.y) * (right.x - left.x) < (right.y - left.y) * (point.x - left.x))
//inside = !inside;
//
//oldPoint = newPoint;
//oldSqDist = newSqDist;
//}
//
//return inside;
