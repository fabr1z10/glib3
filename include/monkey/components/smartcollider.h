#pragma once

#include <monkey/components/icollider.h>

class Animator;
class BoxedModel;
class Renderer;
class StateMachine;

struct SmartCollisionDetails {
    int flag;
    int mask;
    int tag;
};

/*
 * A smart collider needs to be used with a boxed model.
 * A boxed model is a model with collision boxes associated to each frame.
 *
 * When
 *
 */
class SmartCollider : public ICollider {
public:
    SmartCollider(int flag, int mask, int tag) : ICollider(), m_flag(flag), m_mask(mask), m_tag(tag) {}
    SmartCollider(const SmartCollider&);
    SmartCollider (const ITable&);
    void Start() override;
    void Update(double) override {}
    Shape* GetShape() override;
    int GetCollisionTag() const override;
    int GetCollisionFlag() const override;
    int GetCollisionMask() const override;
    int setCollisionMask(int);
    std::shared_ptr<Component> clone() const override;
    std::type_index GetType() override;
    void onFrameUpdate(Animator*a);
    void AddAttackTag(const std::string& anim, int tag, int mask);
    Bounds getAttackBounds() const override;
    void addStateCollisionDetails (const std::string&, int flag, int mask, int tag);
private:
    StateMachine* m_stateMachine;
    Animator* m_animator;
    BoxedModel* m_model;
    Renderer* m_colliderRenderer;
    Bounds GetStaticBoundsI() const override;
    Bounds GetDynamicBoundsI() const override;

    int m_flag;
    int m_mask;
    int m_tag;

    // one per state
    std::unordered_map<std::string, SmartCollisionDetails> m_collisionDetailsOverride;

    std::unordered_map<std::string, std::pair<int, int>> m_attackInfo;
};
