#pragma once

#include <memory>
#include "gfx/math/shape.h"
#include "gfx/component.h"
#include <gfx/event.h>

class Entity;
class CollisionEngine;

class Collider : public Component {
public:
    Collider (int tag, int flag, int mask) : m_shape{nullptr}, m_engine{nullptr}, m_tag{tag}, m_flag{flag}, m_mask{mask}, m_enabled{true} {}
    Collider (std::shared_ptr<Shape> shape, int tag, int flag, int mask) : m_shape{shape}, m_tag{tag}, m_enabled{true}, m_flag{flag}, m_mask{mask} {}
    Collider (const Collider&);
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
    int GetFlag() const;
    int GetMask() const;
    Event<Collider*> onShapeChanged;
    void SetEnabled (bool);
    std::shared_ptr<Component> clone() const override;
protected:
    int m_flag;
    int m_mask;
    int m_tag;
    std::shared_ptr<Shape> m_shape;
    Bounds m_aabb;
    bool m_enabled;
    CollisionEngine* m_engine;
};

inline Bounds Collider::GetBounds() const {
    return m_aabb;
}

inline Shape* Collider::GetShape() {
    return m_shape.get();
}

inline bool Collider::Enabled() const {
    return m_enabled && IsActive();
}

inline void Collider::SetEnabled(bool value) {
    m_enabled = value;
}

inline int Collider::GetTag() const {
    return m_tag;

}

inline int Collider::GetFlag() const {
    return m_flag;
}

inline int Collider::GetMask() const {
    return m_mask;
}
