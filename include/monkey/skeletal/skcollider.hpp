#pragma once

#include <monkey/components/icollider.h>
#include <monkey/components/renderer.h>
#include <monkey/components/skeletalrenderer.h>


class SkModel;
class SkAnimator;
struct PointLocator;
class MultiRenderer;


// helper class used to draw the skeletal collider boxes

struct SBox {
    int jointId;
    unsigned offset;
    unsigned count;

};

class SkeletalColliderRenderer : public Renderer {
public:
    SkeletalColliderRenderer(SkeletalRenderer* renderer, std::shared_ptr<Model>& model, SkModel* skeletal);
    void Draw(Shader*) override;
    //void setShapeInfo(const std::vector<std::pair<unsigned, unsigned>>&);
    std::type_index GetType() override;
    //void Start() override;
    void Update(double) override;

    void addBox(const std::string& animation, int joint, unsigned offset, unsigned count);
private:
    std::unordered_map<std::string, std::vector<SBox>> m_boxInfos;
    SkeletalRenderer* m_renderer;
    SkModel* m_skeletalModel;

};


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
    SkCollider (const ITab&);
    void Start() override;
    void Begin() override;

    void Update(double) override;
    IShape* GetShape() override;


    //int setCollisionMask(int);
    std::type_index GetType() override;
    Bounds getAttackBounds() const override;
    //void computeAttackBoxes();
//    std::shared_ptr<IShape> getBox(const std::string& anim, float t, const std::vector<PointLocator>& pts,
//                                  const std::vector<glm::vec2>& fixedPoints = std::vector<glm::vec2>());
    float getAttackDistance() const override;

private:
    void recalcShapesDebug();
    void updateShape();
    int m_shapeId;
    SkeletalRenderer* m_renderer;
    Entity* m_shapeEntity;
    //std::vector<Renderer*> m_colliderRenderers;
    //Renderer* m_mainRenderer;
    SkModel* m_model;
    Bounds GetStaticBoundsI() const override;
    Bounds GetDynamicBoundsI() const override;

    int m_castTag;
    int m_castMask;
};
