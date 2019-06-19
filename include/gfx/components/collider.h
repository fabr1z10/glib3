#pragma once

#include <memory>
#include "gfx/math/shape.h"
#include "gfx/components/icollider.h"
#include <gfx/event.h>

class Entity;
class CollisionEngine;

class SimpleCollider : public ICollider {
public:
    SimpleCollider (int tag, int flag, int mask) : m_shape{nullptr}, m_engine{nullptr}, m_tag{tag}, m_flag{flag}, m_mask{mask}, m_enabled{true} {}
    SimpleCollider (std::shared_ptr<Shape> shape, int tag, int flag, int mask) :
    m_shape{shape}, m_tag{tag}, m_enabled{true}, m_flag{flag}, m_mask{mask}, m_engine(nullptr) {}
    SimpleCollider (const SimpleCollider&);
    virtual ~SimpleCollider();
    
    // ICollider interface
    Shape* GetShape() override;
    int GetCollisionTag() const override;
    int GetCollisionFlag() const override;
    int GetCollisionMask() const override;
    
    
    bool HasShape() const;
    void SetShape(std::shared_ptr<Shape> shape);
    void SetParent(Entity* parent) override;
    void Start() override;
    void End() override;
    void Update(double) override {}
    void Move(Entity*);
    using ParentClass = ICollider;
    bool Enabled() const;
    Bounds GetBounds() const;
    Event<SimpleCollider*> onShapeChanged;
    void SetEnabled (bool);
    CollisionEngine* GetCollisionEngine() { return m_engine;}
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

inline Bounds SimpleCollider::GetBounds() const {
    return m_aabb;
}

inline Shape* SimpleCollider::GetShape() {
    return m_shape.get();
}

inline bool SimpleCollider::Enabled() const {
    return m_enabled && isActive();
}

inline void SimpleCollider::SetEnabled(bool value) {
    m_enabled = value;
}

inline int SimpleCollider::GetCollisionTag() const {
    return m_tag;

}

inline int SimpleCollider::GetCollisionFlag() const {
    return m_flag;
}

inline int SimpleCollider::GetCollisionMask() const {
    return m_mask;
}

inline bool SimpleCollider::HasShape() const {
    return m_shape != nullptr;
}
