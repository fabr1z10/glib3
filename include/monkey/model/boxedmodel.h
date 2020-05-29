#pragma once

#include <monkey/model/spritemodel.h>
#include <monkey/math/shape.h>
#include <monkey/hashpair.h>

class BoxedModel : public SpriteModel {
public:
    explicit BoxedModel (std::shared_ptr<SpriteMesh> mesh);
    BoxedModel(const ITable& t);
    void addShape (std::shared_ptr<Shape>);
    void setAnimShape (const std::string& anim, int shapeId);
    void setFrameShape (const std::string& anim, int frame, int shapeId);

    void setShape (const std::string& anim, int frame, int shapeId);
    void setShapeCast (const std::string& anim, int frame, int shapeId);

    //const BoxInfo& getBoxInfo(const std::string& anim, int frame) const;
    void AddAnimationData (const std::string& anim, Bounds b);
    void AddCollisionData (const std::string& anim, int frame,
                           std::shared_ptr<Shape> collision);
                           //std::shared_ptr<Shape> attack);
    void AddAttackData (const std::string& anim, int frame, std::shared_ptr<Shape> attack);
    std::shared_ptr<Shape> getShape (const std::string&, int);
    std::shared_ptr<Shape> getShapeCast (const std::string&, int);
    std::shared_ptr<Shape> shape(int);
    int getShapeId (const std::string&, int);
    int getShapeCastId (const std::string&, int);
    void generateDebugMesh ();
    std::shared_ptr<IMesh> GetCollisionMesh();
    Bounds GetMaxBounds() const;
    Bounds GetAnimBounds(const std::string&) const;
    const std::vector<std::shared_ptr<Shape>>& getShapes();
private:
    std::vector<std::shared_ptr<Shape>> m_shapes;
    std::unordered_map<std::pair<std::string, int>, int> m_boxInfo;
    std::unordered_map<std::pair<std::string, int>, int> m_shapeCast;

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

inline const std::vector<std::shared_ptr<Shape>>& BoxedModel::getShapes() {
    return m_shapes;
}
//inline const BoxInfo& BoxedModel::getBoxInfo(const std::string& anim, int frame) const {
//    return m_boxInfo.at(std::make_pair(anim, frame));
//}
