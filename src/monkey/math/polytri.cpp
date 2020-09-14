#include <monkey/math/shapes/polytri.h>
#include <monkey/math/earcut.h>
#include <monkey/math/triangle.h>

PolyTri::PolyTri(const ITable& t) : CompoundShape() {
    auto outline = t.get<std::vector<float> >("outline");
    

    // The number type to use for tessellation
    using Coord = float;
    
    // The index type. Defaults to uint32_t, but you can also pass uint16_t if you know that your
    // data won't have more than 65536 vertices.
    using N = uint32_t;
    
    // Create array
    using Point = std::array<Coord, 2>;
    std::vector<std::vector<Point>> polygon;
    std::vector<Point> op;
    //m_bounds.min = glm::vec3(outline[0], outline[1], 0.0f);
    //m_bounds.max = glm::vec3(outline[0], outline[1], 0.0f);

    for (size_t i = 0; i < outline.size(); i = i + 2) {
        glm::vec2 P(outline[i], outline[i+1]);
        m_points.push_back(P);
        op.push_back({outline[i], outline[i+1]});

    }
    polygon.push_back(op);
    // Run tessellation
    // Returns array of indices that refer to the vertices of the input polygon.
    // e.g: the index 6 would refer to {25, 75} in this example.
    // Three subsequent indices form a triangle. Output triangles are clockwise.
    m_tri = mapbox::earcut<N>(polygon);

    // calculate edges
    for (int i = 0; i < m_tri.size(); i += 3) {

        this->AddShape(std::make_shared<Triangle>(
            m_points[m_tri[i]],
            m_points[m_tri[i+1]],
            m_points[m_tri[i+2]]
        ));
    }
    
}


void PolyTri::accept (AcyclicVisitor& v) {
    Visitor<PolyTri>* v1 = dynamic_cast<Visitor<PolyTri>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a polytri visitor");
}
//
//bool PolyTri::isPointInside(glm::vec3 point) const {
//    int i, j;
//    bool c = false;
//    int nvert = m_points.size();
//    for (i = 0, j = nvert-1; i < nvert; j = i++) {
//        if ( ((m_points[i].y > point.y) != (m_points[j].y > point.y)) &&
//            (point.x < (m_points[j].x-m_points[i].x) * (point.y-m_points[i].y) / (m_points[j].y-m_points[i].y) + m_points[i].x) )
//            c = !c;
//    }
//    return c;
//}
//
//std::vector<glm::vec2> PolyTri::getEdges() {
//    return m_edges;
//}

std::string PolyTri::toString() const {
    return "";
    
}

std::vector<glm::vec2> PolyTri::getPoints() {
    return m_points;
}