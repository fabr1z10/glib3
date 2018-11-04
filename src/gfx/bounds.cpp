#include <gfx/bounds.h>

void Bounds::Transform(const glm::mat4& m){
    glm::vec2 P[4];
    P[0] = glm::vec2(min.x, min.y);
    P[1] = glm::vec2(max.x, min.y);
    P[2] = glm::vec2(max.x, max.y);
    P[3] = glm::vec2(min.x, max.y);
    float inf = std::numeric_limits<float>::infinity();
    min = glm::vec2(inf, inf);
    max = glm::vec2(-inf, -inf);
    for (int i = 0; i < 4; i++) {
        glm::vec2 Pt = glm::vec2(m * glm::vec4(P[i], 0.0f, 1.0f));
        if (Pt.x < min.x)
            min.x = Pt.x;
        else if (Pt.x > max.x)
            max.x = Pt.x;
        if (Pt.y < min.y)
            min.y = Pt.y;
        else if (Pt.y > max.y)
            max.y = Pt.y;
    }
}



void Bounds::Expand(float amount) {
    float ha = amount * 0.5f;
    glm::vec2 halfAmounts(ha, ha);
    min -= halfAmounts;
    max += halfAmounts;
}