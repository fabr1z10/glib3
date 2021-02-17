#include <monkey/contour.h>

void Contour::visit(Segment& line) {
    glm::vec2 O = line.getOffset();
    auto A = line.getA();
    auto B = line.getB();
    m_result.emplace_back(glm::vec3 (O.x + A.x, O.y + A.y, 0.0f));
    m_result.emplace_back(glm::vec3 (O.x + B.x, O.y + B.y, 0.0f));
}

void Contour::visit(Rect & rect) {
    glm::vec2 O = rect.getOffset();
    auto w = rect.getWidth();
    auto h = rect.getHeight();
    std::vector <glm::vec3> points;
    m_result.emplace_back(glm::vec3 (O.x, O.y, 0.0f));
    m_result.emplace_back(glm::vec3 (O.x + w, O.y, 0.0f));
    m_result.emplace_back(glm::vec3 (O.x + w, O.y + h, 0.0f));
    m_result.emplace_back(glm::vec3 (O.x, O.y + h, 0.0f));
    m_result.emplace_back(glm::vec3 (O.x, O.y, 0.0f));
}
//
//void Contour::visit(Box3D & rect) {
//    glm::vec2 O = rect.GetOffset();
//    auto w = rect.width();
//    auto h = rect.height();
//    std::vector <glm::vec3> points;
//    m_result.emplace_back(glm::vec3 (O.x, O.y, 0.0f));
//    m_result.emplace_back(glm::vec3 (O.x + w, O.y, 0.0f));
//    m_result.emplace_back(glm::vec3 (O.x + w, O.y + h, 0.0f));
//    m_result.emplace_back(glm::vec3 (O.x, O.y + h, 0.0f));
//    m_result.emplace_back(glm::vec3 (O.x, O.y, 0.0f));
//
//}

std::vector<glm::vec3> Contour::CreateContour (IShape* s) {
    Contour c;
    //s->accept(c);
    return c.m_result;
}
