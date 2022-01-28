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
    int isStatic;

};

class SkeletalColliderRenderer : public Renderer {
public:
    SkeletalColliderRenderer(SkeletalRenderer* renderer, std::shared_ptr<Model>& model, SkModel* skeletal);
    void Draw(Shader*) override;
    //void setShapeInfo(const std::vector<std::pair<unsigned, unsigned>>&);
    std::type_index GetType() override;
    //void Start() override;
    void Update(double) override;

    void addBox(const std::string& animation, int joint, unsigned offset, unsigned count, bool);
private:
    std::unordered_map<std::string, std::vector<SBox>> m_boxInfos;
    SkeletalRenderer* m_renderer;
    SkModel* m_skeletalModel;

};

struct ShapeCastInfo {
    std::shared_ptr<IShape> shape;
    int jointId;
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
	glm::vec2 getAttackDistance() const override;

private:
    void recalcShapesDebug();
    void updateShape();
    int m_shapeId;
    SkeletalRenderer* m_renderer;
    Entity* m_shapeEntity;
    //std::vector<Renderer*> m_colliderRenderers;
    //Renderer* m_mainRenderer;
    std::unordered_map<std::string, ShapeCastInfo> m_castShapes;
    std::unordered_map<std::string, std::shared_ptr<IShape>> m_shapes;
    std::shared_ptr<IShape> m_staticShape;
    SkModel* m_model;
    Bounds GetStaticBoundsI() const override;
    Bounds GetDynamicBoundsI() const override;
    std::pair<unsigned, unsigned> addDebugMesh(std::vector<VertexSkeletalColor>& vertices, std::vector<unsigned>& indices,
                                               float x, float y, float w, float h, glm::vec3 color);
    int m_castTag;
    int m_castMask;
    glm::vec2 m_attackDistance;
    ICollider* m_lastHit;
};
