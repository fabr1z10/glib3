#include <gfx/contour.h>

void Contour::visit(Line & line) {
    glm::vec2 O = line.GetOffset();
    auto A = line.getA();
    auto B = line.getB();
    m_result.emplace_back(glm::vec3 (O.x + A.x, O.y + A.y, 0.0f));
    m_result.emplace_back(glm::vec3 (O.x + B.x, O.y + B.y, 0.0f));
}

void Contour::visit(Rect & rect) {
    glm::vec2 O = rect.GetOffset();
    auto w = rect.GetWidth();
    auto h = rect.GetHeight();
    std::vector <glm::vec3> points;
    m_result.emplace_back(glm::vec3 (O.x, O.y, 0.0f));
    m_result.emplace_back(glm::vec3 (O.x + w, O.y, 0.0f));
    m_result.emplace_back(glm::vec3 (O.x + w, O.y + h, 0.0f));
    m_result.emplace_back(glm::vec3 (O.x, O.y + h, 0.0f));
    m_result.emplace_back(glm::vec3 (O.x, O.y, 0.0f));
}


std::vector<glm::vec3> Contour::CreateContour (Shape* s) {
    Contour c;
    s->accept(c);
    return c.m_result;
}
