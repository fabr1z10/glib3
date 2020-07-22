//#pragma once
//
//#include <monkey/assets/imodel.h>
//#include <monkey/texturedmesh.h>
//
//
//struct SkeletalBone {
//    SkeletalBone(const std::string& id, glm::vec2 pos);
//    std::string id;
//    glm::vec2 pos;
//    glm::mat4 localTransform;
//    glm::mat4 worldTransform;
//    SkeletalBone* parent;
//    std::vector<SkeletalBone*> children;
//};
//
//class SkeletalModel2 : public IModel {
//public:
//    SkeletalModel2 (const ITable&);
//
//    Bounds GetBounds() const override;
//
//    void Draw (Shader*, const std::unordered_map<std::string, glm::mat4>& bonesTransform);
////    Bounds getBoundingBox(const std::vector<float>& angles);
//    ShaderType GetShaderType() const override;
//
//    // create a hierarchy of bones
//    void addBone(const std::string& id, glm::vec2 pos, const std::string& parent = "");
//    std::vector<std::string> GetAnimations() const override { return std::vector<std::string>(); }
//    std::string GetDefaultAnimation() const override { return ""; }
//
//    //    void addAnimation (const std::string& id, std::shared_ptr<SkeletalAnimation> anim);
//    //Shape* getBounds (const std::string& anim);
//
//private:
//    void recalcBones();
//    SkeletalBone* m_root;
//    std::unordered_map<std::string, int> m_bonesMap;
//    std::vector<SkeletalBone> m_bones;
//    std::vector<glm::mat4> m_boneTransform;
//    std::shared_ptr<TexturedMesh<VertexSkeletal> > m_mesh;
//
//};
//
////inline const std::unordered_map<std::string, SkeletalAttackInfo>& SkeletalModel::getAttackInfos() {
////    return m_attackInfo;
////};