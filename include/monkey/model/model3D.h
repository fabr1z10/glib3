//#pragma once
//
//#include <monkey/imodel.h>
//#include <memory>
//#include <map>
//
//struct KeyFrame {
//    std::unordered_map<std::string, glm::mat4> keyTransforms;
//};
//
//struct Animation3DInfo {
//    float duration;
//    std::map<float, KeyFrame> keyFrames;
//};
//
//class Model3D : public IModel {
//public:
//    Model3D ();
//    Bounds3D GetBounds() const override;
//    std::vector<std::string> GetAnimations() const override;
//    std::string GetDefaultAnimation() const override;
//    ShaderType GetShaderType() const override;
//    const Animation3DInfo* GetAnimInfo() const;
//    const Animation3DInfo* GetAnimInfo(const std::string&) const;
//    virtual void Draw (Shader*, int offset, int count) override;
//
//private:
//    std::unordered_map<std::string, Animation3DInfo> m_animData;
//    std::vector<std::shared_ptr<IMesh>> m_meshes;
//};
//
//class Model3DFactory {
//public:
//    static std::shared_ptr<IMesh> CreatePlane (float width, float depth, glm::vec4);
//    static std::shared_ptr<IMesh> CreateBox (float width, float depth, float height, glm::vec4);
//};
//
