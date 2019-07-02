#pragma once

#include <gfx/model/spritemodel.h>
#include <gfx/math/shape.h>
#include <gfx/hashpair.h>

struct BoxInfo {
    std::shared_ptr<Shape> m_shape;
    std::shared_ptr<Shape> m_attackShape;
    //int shapeTag;
    //int attackTag;
    int offset;
    int count;
};

class BoxedModel : public SpriteModel {
public:
    explicit BoxedModel (std::shared_ptr<SpriteMesh> mesh);

    const BoxInfo& getBoxInfo(const std::string& anim, int frame) const;
    void AddAnimationData (const std::string& anim, Bounds b);
    void AddCollisionData (const std::string& anim, int frame,
                           std::shared_ptr<Shape> collision,
                           std::shared_ptr<Shape> attack);
    std::shared_ptr<Shape> GetShape (const std::string&, int);
    void generateDebugMesh ();
    std::shared_ptr<IMesh> GetCollisionMesh();
    Bounds GetMaxBounds() const;
    Bounds GetAnimBounds(const std::string&) const;
private:
    std::unordered_map<std::pair<std::string, int>, BoxInfo> m_boxInfo;
    std::unordered_map<std::string, Bounds> m_animBounds;
    int addShapeMesh(const std::shared_ptr<Shape>&, int& pc, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices);
    std::shared_ptr<IMesh> m_collisionMesh;
    Bounds m_maxBounds;
};

inline Bounds BoxedModel::GetMaxBounds() const {
    return m_maxBounds;

}

inline std::shared_ptr<IMesh> BoxedModel::GetCollisionMesh() {
    return m_collisionMesh;
}

inline const BoxInfo& BoxedModel::getBoxInfo(const std::string& anim, int frame) const {
    return m_boxInfo.at(std::make_pair(anim, frame));
}
