#pragma once

#include <monkey/assets/imodel.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model3D : public IModel {
public:
    //SkModel (const ITable&);
    Model3D(const ITab &);
    Bounds GetBounds() const override;
    std::vector<std::string> GetAnimations() const override;
    std::string GetDefaultAnimation() const override;
    ShaderType GetShaderType() const override;
    void draw(Shader*, int offset = 0, int count = 0) override;
private:
    void loadModel(const std::string& path);
    void processNode(aiNode *node, const aiScene *scene);
};