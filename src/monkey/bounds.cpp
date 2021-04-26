#include <monkey/bounds.h>
#include <algorithm>

void Bounds::Translate(const glm::vec3 & disp) {
    min += disp;
    max += disp;

}

Bounds Bounds::intersect(const Bounds &other) {
    Bounds b;
    b.min.x = std::max(this->min.x, other.min.x);
    b.min.y = std::max(this->min.y, other.min.y);
    b.max.x = std::min(this->max.x, other.max.x);
    b.max.y = std::min(this->max.y, other.max.y);
    return b;

}

void Bounds::Transform(const glm::mat4& m) {
    glm::vec3 P[] = {
        glm::vec3(min.x, min.y, min.z),
        glm::vec3(max.x, min.y, min.z),
        glm::vec3(max.x, max.y, min.z),
        glm::vec3(min.x, max.y, min.z),
        glm::vec3(min.x, min.y, max.z),
        glm::vec3(max.x, min.y, max.z),
        glm::vec3(max.x, max.y, max.z),
        glm::vec3(min.x, max.y, max.z),
    };

    float inf = std::numeric_limits<float>::infinity();
    min = glm::vec3(inf, inf, inf);
    max = glm::vec3(-inf, -inf, -inf);
    for (int i = 0; i < 8; i++) {
        glm::vec3 Pt = glm::vec3(m * glm::vec4(P[i], 1.0f));
        if (Pt.x < min.x)
            min.x = Pt.x;
        else if (Pt.x > max.x)
            max.x = Pt.x;
        if (Pt.y < min.y)
            min.y = Pt.y;
        else if (Pt.y > max.y)
            max.y = Pt.y;
        if (Pt.z < min.z)
            min.z = Pt.z;
        else if (Pt.z > max.z)
            max.z = Pt.z;
    }
}

//void Bounds::TransformXZ(const glm::mat4& m){
//    glm::vec2 P[4];
//    P[0] = glm::vec2(min.x, min.y);
//    P[1] = glm::vec2(max.x, min.y);
//    P[2] = glm::vec2(max.x, max.y);
//    P[3] = glm::vec2(min.x, max.y);
//    float inf = std::numeric_limits<float>::infinity();
//    min = glm::vec2(inf, inf);
//    max = glm::vec2(-inf, -inf);
//    for (int i = 0; i < 4; i++) {
//        auto result = m * glm::vec4(P[i][0], 0.0f, P[i][1], 1.0f);
//        glm::vec2 Pt (result.x, result.z);
//        if (Pt.x < min.x)
//            min.x = Pt.x;
//        else if (Pt.x > max.x)
//            max.x = Pt.x;
//        if (Pt.y < min.y)
//            min.y = Pt.y;
//        else if (Pt.y > max.y)
//            max.y = Pt.y;
//    }
//}

void Bounds::Expand(float amount) {
    float ha = amount * 0.5f;
    glm::vec3 halfAmounts(ha, ha, ha);
    min -= halfAmounts;
    max += halfAmounts;
}

void Bounds::addPoint(glm::vec3 P) {
    min.x = std::min(min.x, P.x);
    min.y = std::min(min.y, P.y);
    max.x = std::max(max.x, P.x);
    max.y = std::max(max.y, P.y);

}

void Bounds::ExpandWith(const Bounds & b) {
    if (isVoid()) {
        min = b.min;
        max = b.max;
    } else {
        min.x = std::min(min.x, b.min.x);
        min.y = std::min(min.y, b.min.y);
        max.x = std::max(max.x, b.max.x);
        max.y = std::max(max.y, b.max.y);
    }
}