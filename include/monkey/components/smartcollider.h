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
    SmartColliderRenderer(std::shared_ptr<Model> model,
                          const std::vector<std::pair<unsigned, unsigned>>&, BoxedModel*, SpriteRenderer*);
    void Draw(Shader*) override;
    //void setShapeInfo(const std::vector<std::pair<unsigned, unsigned>>&);
    std::type_index GetType() override;
    void Start() override;

private:
    SpriteRenderer* m_renderer;
    BoxedModel* m_boxedModel;
    std::vector<std::pair<unsigned, unsigned>> m_shapeInfo;
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
    //SmartCollider(int flag, int mask, int tag) : ICollider(), m_flag(flag), m_mask(mask), m_tag(tag) {}
    ~SmartCollider() override;
    SmartCollider (const ITab&);
    void Start() override;
    void Update(double) override;
    IShape* GetShape() override;

    int setCollisionMask(int);
    std::type_index GetType() override;
	//void onFrameUpdate(Animator*a);
    void AddAttackTag(const std::string& anim, int tag, int mask);
    Bounds getAttackBounds() const override;
    void addStateCollisionDetails (const std::string&, int flag, int mask, int tag);
	glm::vec2 getAttackDistance() const override;

private:
    StateMachine* m_stateMachine;
    SpriteRenderer* m_animator;
    BoxedModel* m_model;
    MultiRenderer* m_colliderRenderer;
    Bounds GetStaticBoundsI() const override;
    Bounds GetDynamicBoundsI() const override;
    Entity* m_shapeEntity;

    int m_castTag;
    int m_castMask;

    // one per state
    std::unordered_map<std::string, SmartCollisionDetails> m_collisionDetailsOverride;

    std::unordered_map<std::string, std::pair<int, int>> m_attackInfo;
    ICollider* m_lastHit;

};
