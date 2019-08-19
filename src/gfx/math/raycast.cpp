#include <gfx/math/raycast.h>
#include <gfx/math/geom.h>

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

RayCastHit RayCast2D::SegmentIntersection(glm::vec2 A, glm::vec2 B, std::vector<glm::vec2>& p)
{
    p.push_back(p.front());
    RayCastHit ret;
    ret.collide = false;
    ret.length = m_length;
    for (int i = 1; i < p.size(); ++i) {
        glm::vec2 Cw (m_transform * glm::vec4(p[i-1], 0.0f, 1.0f));
        glm::vec2 Dw (m_transform * glm::vec4(p[i], 0.0f, 1.0f));
        float l = SegmentIntersection(m_A, m_B, Cw, Dw);
        if (l < ret.length) {
            ret.collide = true;
            ret.length = l;
            ret.normal = glm::vec3(glm::normalize(Perp(Dw-Cw)), 0.0f);
        }
    }
    return ret;
}

RayCastHit RayCast2D::SegmentIntersectionSimple(glm::vec2 A, glm::vec2 B, std::vector<glm::vec2>& p)
{
    p.push_back(p.front());
    RayCastHit ret;
    ret.collide = false;
    ret.length = m_length;
    for (int i = 1; i < p.size(); ++i) {
        float l = SegmentIntersection(A, B, p[i-1], p[i]);
        if (l < ret.length) {
            ret.collide = true;
            ret.length = l;
            ret.normal = glm::vec3(glm::normalize(Perp(p[i]-p[i-1])), 0.0f);
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
        m_result.normal = glm::vec3(glm::normalize(Perp(Dw-Cw)), 0.0f);
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

void RayCast2D::visit(Poly & p) {
    auto cont = p.GetPolygon();
    auto points = cont->getPoints();
    m_result = SegmentIntersection(m_A, m_B, points);
    if (!m_result.collide) {

        const auto& holes = p.getHoles();
        for (const auto& hole : holes) {
            const auto& wt = hole.getWorldTransform();
            const auto& iwt = glm::inverse(wt);
            glm::vec2 lA (iwt * glm::vec4(m_A, 1.0f));
            glm::vec2 lB (iwt * glm::vec4(m_B, 1.0f));
            auto points = hole.getPolygon()->getPoints();

            m_result = SegmentIntersectionSimple (lA, lB, points);
            if (m_result.collide) {
                m_result.normal = glm::vec3(wt * glm::vec4(m_result.normal, 0.0f));
                return;
            }

        }

    }

}


void RayCast2D::visit(Circle& c) {
    glm::vec3 C(m_transform * glm::vec4(c.getPoints()[0], 0.0f, 1.0f));
    glm::vec3 a = m_A - C;
    glm::vec3 b = m_B - C;
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

#include <iostream>
void RayCast2D::visit(Plane3D& s) {
    // first, let's transform the ray into obejct coords
    auto t = glm::inverse(m_transform);
    glm::vec3 P0 (t * glm::vec4(m_A, 1.0f));
    glm::vec3 dl (t * glm::vec4(m_dir, 0.0f));
    float k = -P0.y / dl.y;
    if (k < 0 || k > m_length) {
        return;
    }
    glm::vec3 ip = P0 + k*dl;
    if (!s.isPointInside(ip))
        return;
    // collision here
    m_result.length = k;
    m_result.collide = true;
    glm::vec3 normal_local = P0.y < 0 ? monkey::down : monkey::up;
    m_result.normal = glm::vec3(m_transform * glm::vec4(normal_local, 0.0f));


}


#include <iostream>
void RayCast2D::visit(Box& s) {
    // first, let's transform the ray into obejct coords
    auto it = glm::inverse(m_transform);
    glm::vec3 P0 (it * glm::vec4(m_A, 1.0f));
    glm::vec3 dl (it * glm::vec4(m_dir, 0.0f));
    if (s.isPointInside(P0))
        return;
    glm::vec3 P1 = P0 +dl*m_length;
    if (!s.isPointInside(P1))
        return;
    float w = s.width();
    float h = s.height();
    float d = s.depth();
    glm::vec3 o = s.GetOffset();
    // check collision with right face
    float tm = std::numeric_limits<float>::infinity();
    glm::vec3 bestNormal;
    // hit with right side
    if (dl.x != 0.0f) {
        float t = ((w + o.x) - P0.x) / dl.x;
        if (t >= 0 && t <= m_length && t < tm) {
            tm = t;
            bestNormal = monkey::right;
        }
        t = (o.x - P0.x) / dl.x;
        if (t >= 0 && t <= m_length && t < tm) {
            tm = t;
            bestNormal = monkey::left;
        }
    }
    if (dl.y != 0.0f) {
        float t = ((h + o.y) - P0.y) / dl.y;
        if (t >= 0 && t <= m_length && t < tm) {
            tm = t;
            bestNormal = monkey::up;
        }
        t = (o.y - P0.y) / dl.y;
        if (t >= 0 && t <= m_length && t < tm) {
            tm = t;
            bestNormal = monkey::down;
        }
    }
    if (dl.z != 0.0f) {
        float t = ((d + o.z) - P0.z) / dl.z;
        if (t >= 0 && t <= m_length && t < tm) {
            tm = t;
            bestNormal = monkey::front;
        }
        t = (o.z - P0.z) / dl.z;
        if (t >= 0 && t <= m_length && t < tm) {
            tm = t;
            bestNormal = monkey::back;
        }
    }
    // collision here
    m_result.length = tm;
    m_result.collide = true;
    m_result.normal = glm::vec3(m_transform * glm::vec4(bestNormal, 0.0f));


}
