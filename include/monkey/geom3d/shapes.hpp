#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace geom3d {

    enum Shape3DType {
        PLANE, SEGMENT, SPHERE, AABB
    };

    struct Shape3D {
        virtual Shape3DType getType() = 0;
        virtual std::unique_ptr<Shape3D> transform(const glm::mat4&) = 0;
    };

    struct Plane : public Shape3D {
        Plane() : n(glm::vec3(0.0f)), d(0.0f) {}
        glm::vec3 n;    // Plane normal. Points x on the plane satisfy Dot(n,x) = d
        float d;        // distance of the plane from the origin
        Shape3DType getType() override {
            return PLANE;
        }
        std::unique_ptr<Shape3D> transform(const glm::mat4&) override;
    };

    struct Segment : public Shape3D {
        glm::vec3 a;
        glm::vec3 b;
        Shape3DType getType() override {
            return SEGMENT;
        }
        std::unique_ptr<Shape3D> transform(const glm::mat4&) override;
    };

    struct Sphere : public Shape3D {
        glm::vec3 center;
        float radius;
        Shape3DType getType() override {
            return SPHERE;
        }
        std::unique_ptr<Shape3D> transform(const glm::mat4&) override;
    };

    struct AABox : public Shape3D {
        glm::vec3 min;
        glm::vec3 max;
        Shape3DType getType() override {
            return Shape3DType::AABB;
        }
        std::unique_ptr<Shape3D> transform(const glm::mat4&) override;
    };

    // construct a plane given 3 points
    inline Plane computePlane(glm::vec3 a, glm::vec3 b, glm::vec3 c)
    {
        Plane p;
        p.n = glm::normalize(glm::cross(b - a, c - a));
        p.d = glm::dot(p.n, a);
        return p;
    }


}