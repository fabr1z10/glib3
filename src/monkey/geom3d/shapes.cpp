#include <monkey/geom3d/shapes.hpp>

using namespace geom3d;

std::unique_ptr<Shape3D> Plane::transform(const glm::mat4 & m) {
    auto plane = std::make_unique<Plane>();
    auto pp = glm::transpose(glm::inverse(m)) * glm::vec4(n, -d);
    plane->n = glm::vec3(pp);
    plane->d = -pp[3];
    return plane;
}

std::unique_ptr<Shape3D> Segment::transform(const glm::mat4 & m) {
    auto seg = std::make_unique<Segment>();
    seg->a = m * glm::vec4(a, 1.0f);
    seg->b = m * glm::vec4(b, 1.0f);
    return seg;
}

std::unique_ptr<Shape3D> Sphere::transform(const glm::mat4 & m ) {
    auto sph = std::make_unique<Sphere>();
    sph->center = m * glm::vec4(center, 1.0f);
    return sph;

}