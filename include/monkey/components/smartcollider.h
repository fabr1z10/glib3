#pragma once

#include <monkey/components/icollider.h>
#include "renderer.h"

class SpriteRenderer;
class BoxedModel;
class MultiRenderer;
class StateMachine;
class AnimationRenderer;

struct SmartCollisionDetails {
    int flag;
    int mask;
    int tag;
};


class SmartColliderRenderer : public Renderer {
public:
    void Draw(Shader*) override;
private:
    SpriteRenderer* m_renderer;
    BoxedModel* m_model;
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
    ~SmartCollider() override;
    SmartCollider (const ITab&);
    void Start() override;
    void Update(double) override {}
    IShape* GetShape() override;
    int GetCollisionTag() const override;
    int GetCollisionFlag() const override;
    int GetCollisionMask() const override;
    int setCollisionMask(int);
    std::type_index GetType() override;
	//void onFrameUpdate(Animator*a);
    void AddAttackTag(const std::string& anim, int tag, int mask);
    Bounds getAttackBounds() const override;
    void addStateCollisionDetails (const std::string&, int flag, int mask, int tag);
    float getAttackDistance() const override;

private:
    StateMachine* m_stateMachine;
    SpriteRenderer* m_animator;
    BoxedModel* m_model;
    MultiRenderer* m_colliderRenderer;
    Bounds GetStaticBoundsI() const override;
    Bounds GetDynamicBoundsI() const override;
    Entity* m_shapeEntity;
    int m_flag;
    int m_mask;
    int m_tag;
    int m_castTag;
    int m_castMask;

    // one per state
    std::unordered_map<std::string, SmartCollisionDetails> m_collisionDetailsOverride;

    std::unordered_map<std::string, std::pair<int, int>> m_attackInfo;
};
