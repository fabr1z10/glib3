#pragma once

#include <monkey/components/icollider.h>

class SkModel;
class SkAnimator;
struct PointLocator;
class MultiRenderer;
/*
 * A smart collider needs to be used with a skeletal model.
 * You can associate a BOX to each animation, plus attack boxes
 * for (animation/interval) pairs
 *
 *
 */
class SkCollider : public ICollider {
public:
    // ctor and clone
    SkCollider (const ITable&);
    void Start() override;
    void Begin() override;

    void Update(double) override;
    Shape* GetShape() override;

    int GetCollisionTag() const override;
    int GetCollisionFlag() const override;
    int GetCollisionMask() const override;
    int setCollisionMask(int);
    std::type_index GetType() override;
    Bounds getAttackBounds() const override;
    void computeAttackBoxes();
    std::shared_ptr<Shape> getBox(const std::string& anim, float t, const std::vector<PointLocator>& pts,
                                  const std::vector<glm::vec2>& fixedPoints = std::vector<glm::vec2>());
private:
    void recalcShapesDebug();
    void updateShape();
    int m_shapeId;
    SkAnimator* m_animator;
    Entity* m_shapeEntity;
    MultiRenderer* m_colliderRenderer;

    SkModel* m_model;
    Bounds GetStaticBoundsI() const override;
    Bounds GetDynamicBoundsI() const override;
    int m_flag;
    int m_mask;
    int m_tag;
    int m_castTag;
    int m_castMask;
};
