#pragma once

#include <gfx/simplemodel.h>
#include <gfx/math/shape.h>
#include <gfx/hashpair.h>

struct BoxInfo {
    std::shared_ptr<Shape> m_shape;
    std::shared_ptr<Shape> m_attackShape;
    int shapeTag;
    int attackTag;
    int offset;
    int count;
};

class BoxedModel : public SimpleModel {
public:
    explicit BoxedModel (std::shared_ptr<SpriteMesh> mesh);

    const BoxInfo& getBoxInfo(const std::string& anim, int frame) const;
    void AddCollisionData (const std::string& anim, int frame,
                           std::shared_ptr<Shape> collision,
                           std::shared_ptr<Shape> attack);
    std::shared_ptr<Shape> GetShape (const std::string&, int);
    void generateDebugMesh ();
    std::shared_ptr<IMesh> GetCollisionMesh();
private:
    std::unordered_map<std::pair<std::string, int>, BoxInfo> m_boxInfo;
    int addShapeMesh(const std::shared_ptr<Shape>&, int& pc, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices);
    std::shared_ptr<IMesh> m_collisionMesh;
};

inline std::shared_ptr<IMesh> BoxedModel::GetCollisionMesh() {
    return m_collisionMesh;
}

inline const BoxInfo& BoxedModel::getBoxInfo(const std::string& anim, int frame) const {
    return m_boxInfo.at(std::make_pair(anim, frame));
}
