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




}