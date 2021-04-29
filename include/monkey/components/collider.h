#pragma once

#include <memory>
#include "monkey/math/shape.h"
#include "monkey/components/icollider.h"
#include <monkey/event.h>

class Entity;
class CollisionEngine;

class SimpleCollider : public ICollider {
public:
    SimpleCollider (int tag, int flag, int mask) : m_shape{nullptr}, m_tag{tag}, m_flag{flag}, m_mask{mask}, m_enabled{true} {}
    SimpleCollider (const ITab&);
    SimpleCollider (std::shared_ptr<IShape> shape, int tag, int flag, int mask) :
    m_shape{shape}, m_tag{tag}, m_enabled{true}, m_flag{flag}, m_mask{mask} {}
    virtual ~SimpleCollider();
    
    // ICollider interface
    IShape* GetShape() override;
    int GetCollisionTag() const override;
    int GetCollisionFlag() const override;
    int GetCollisionMask() const override;
    
    
    bool HasShape() const;
    void SetShape(std::shared_ptr<IShape> shape);
    void SetParent(Entity* parent) override;
    void Start() override;
    void Update(double) override {}
    using ParentClass = ICollider;
    bool Enabled() const;

    Event<SimpleCollider*> onShapeChanged;
    void SetEnabled (bool);
    std::type_index GetType() override;
    float getAttackDistance() const override;

protected:
    int m_flag;
    int m_mask;
    int m_tag;
    std::shared_ptr<IShape> m_shape;
    Bounds m_aabb;
    bool m_enabled;
private:
    Bounds GetStaticBoundsI() const override;
    Bounds GetDynamicBoundsI() const override;

};

inline Bounds SimpleCollider::GetStaticBoundsI() const {
    return m_aabb;
}

inline Bounds SimpleCollider::GetDynamicBoundsI() const {
    return m_aabb;
}

inline IShape* SimpleCollider::GetShape() {
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
