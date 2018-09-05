#pragma once

#include <memory>
#include "graph/shape.h"
#include "gfx/component.h"

class Entity;

class Collider : public Component {
public:
    Collider (std::shared_ptr<Shape> shape, int tag) : m_shape{shape}, m_tag{tag}, m_enabled{true} {}
    virtual ~Collider();
    Shape* GetShape();
    void SetShape(std::shared_ptr<Shape> shape);
    void SetParent(Entity* parent) override;
    void Start() override;
    void Update(double) override {}
    void Move(Entity*);
    using ParentClass = Collider;
    bool Enabled() const;
    Bounds GetBounds() const;
    int GetTag() const;
private:
    int m_tag;
    std::shared_ptr<Shape> m_shape;
    Bounds m_aabb;
    bool m_enabled;
};

inline Bounds Collider::GetBounds() const {
    return m_aabb;
}

inline Shape* Collider::GetShape() {
    return m_shape.get();
}

inline bool Collider::Enabled() const {
    return m_enabled;
}

inline int Collider::GetTag() const {
    return m_tag;

}