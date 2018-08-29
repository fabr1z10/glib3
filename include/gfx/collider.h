#pragma once

#include <memory>
#include "graph/shape.h"
#include "gfx/component.h"

class Entity;

class Collider : public Component {
public:
    Collider (std::shared_ptr<Shape> shape) : m_shape{shape} {}
    Shape* GetShape();
    void SetShape(std::shared_ptr<Shape> shape);
    void SetParent(Entity* parent) override;
    void Start() override {}
    void Update(double) override {}

    using ParentClass = Collider;
private:
    std::shared_ptr<Shape> m_shape;
};