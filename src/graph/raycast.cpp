#include <graph/raycast.h>
#include <graph/geom.h>

float RayCast2D::SegmentIntersection(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D) {

    // check if A and B are same side of BC
    glm::vec2 CD = D - C;
    float a = cross(C-A, CD);
    if (sign(a) == sign(cross(C-B, CD)))
        return std::numeric_limits<float>::infinity();

    glm::vec2 AB = B - A;
    if (sign(cross (A - C, AB)) == sign(cross(A-D, AB)))
        return std::numeric_limits<float>::infinity();

    // if we get here, we definitely are intersecting, so let's compute
    return (a / cross(AB, CD)) * glm::length(AB);


}

RayCastHit2D RayCast2D::SegmentIntersection(glm::vec2 A, glm::vec2 B, std::vector<glm::vec2>& p)
{
    p.push_back(p.front());
    RayCastHit2D ret;
    ret.collide = false;
    ret.length = m_length;
    for (int i = 1; i < p.size(); ++i) {
        glm::vec2 Cw (m_transform * glm::vec4(p[i-1], 0.0f, 1.0f));
        glm::vec2 Dw (m_transform * glm::vec4(p[i], 0.0f, 1.0f));
        float l = SegmentIntersection(m_A, m_B, Cw, Dw);
        if (l < ret.length) {
            ret.collide = true;
            ret.length = l;
        }
    }
    return ret;
}

void RayCast2D::visit(Line& l) {
    glm::vec2 Cw (m_transform * glm::vec4(l.getA(), 0.0f, 1.0f));
    glm::vec2 Dw (m_transform * glm::vec4(l.getB(), 0.0f, 1.0f));
    float t = SegmentIntersection(m_A, m_B, Cw, Dw);
    if (t == std::numeric_limits<float>::infinity()) {
        m_result.collide = false;
        m_result.length = m_length;
    } else {
        m_result.collide = true;
        m_result.length = t;
    }
}

void RayCast2D::visit(Rect& r) {
    auto points = r.getPoints();
    m_result = SegmentIntersection(m_A, m_B, points);
}

void RayCast2D::visit(Polygon& p) {
    auto points = p.getPoints();
    m_result = SegmentIntersection(m_A, m_B, points);
}

void RayCast2D::visit(Circle& c) {
    glm::vec2 C(m_transform * glm::vec4(c.getPoints()[0], 0.0f, 1.0f));
    glm::vec2 a = m_A - C;
    glm::vec2 b = m_B - C;
    float a2 = a.x*a.x + a.y*a.y;
    float b2 = b.x*b.x + b.y*b.y;
    float c2 = c.GetRadius() * c.GetRadius();
    if ((a2 < c2 && b2 < c2) || (a2 > c2 && b2 > c2)) {
        m_result.collide = false;
    } else {
        m_result.collide = true;
        float a = length2(m_B - m_A);
        float b = 2.0f * ((m_B.x-m_A.x)*(m_A.x-C.x) + (m_B.y-m_A.y)*(m_A.y-C.y));
        float c = length2(C - m_A) - c2;
        m_result.length = GetFirstSolution (a,b,c);
    }
}

void RayCast2D::visit(CompoundShape& s) {
    auto shapes = s.GetShapes();
    for (auto& c : shapes) {
        RayCast2D r(m_A, m_dir, m_length, m_transform);
        c->accept(r);
        auto pr = r.GetResult();
        if (pr.collide && (!m_result.collide || m_result.length > pr.length)) {
            m_result = pr;
        }
    }
}