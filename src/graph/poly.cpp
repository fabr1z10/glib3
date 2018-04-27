#include "graph/poly.h"
#include "graph/geom.h"


bool Poly::isVertexConcave(int i, int polyId) {
    std::vector<glm::vec2>& p = m_polygons[polyId];
    int n = p.size();
    glm::vec2 next = p[i+1 % n];
    glm::vec2 prev = p[i == 0 ? n-1 : i-1];
    glm::vec2 left = p[i] - prev;
    glm::vec2 right = next - p[i];
    float x = cross(left, right);
    return x < 0;
}