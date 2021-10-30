#pragma once

#include <monkey/assets/model.h>
#include <monkey/spritemesh.h>
#include <monkey/components/renderer.h>
#include <monkey/yaml.h>

class __attribute__ ((visibility ("default"))) SpriteModel : public Model {
public:
//    explicit SpriteModel (std::shared_ptr<SpriteMesh> mesh) : m_mesh(mesh) {
//
//    }
    SpriteModel (const ITab&);
    //Bounds GetBounds() const override;
    std::vector<std::string> GetAnimations() const ;
    std::string GetDefaultAnimation() const ;
    ShaderType GetShaderType() const ;
    const AnimInfo* GetAnimInfo() const;
    const AnimInfo* GetAnimInfo(const std::string&) const;

    // TODO non è meglio avere un draw con animation e frame?
    void draw (Shader*, int offset, int count);

//    std::vector<std::shared_ptr<IShape>> getAttackShapes() const override;

private:
    std::shared_ptr<SpriteMesh> m_mesh;
    //void readFrames(PyDict&);
};

//inline Bounds SpriteModel::GetBounds() const {
//    return m_mesh->GetBounds();
//}

//inline ModelType SpriteModel::GetType() const {
//    return ModelType::SIMPLESPRITE;
//}

//inline std::shared_ptr<IMesh> SpriteModel::GetModel() {
//    return m_mesh;
//}