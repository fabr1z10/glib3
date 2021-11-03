#pragma once

#include <monkey/assets/model.h>
#include <monkey/multitexmesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model3D : public Model {
public:
    //SkModel (const ITable&);
    Model3D(const ITab &);
    Bounds GetBounds() const ;
    std::vector<std::string> GetAnimations() const ;
    std::string GetDefaultAnimation() const ;
    ShaderType GetShaderType() const ;
    void draw(Shader*, int offset = 0, int count = 0) ;
private:
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene *scene);

    std::shared_ptr<IMesh> processMesh(aiMesh* mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
private:
    std::string m_baseDirectory;
    std::vector<std::shared_ptr<IMesh>> m_meshes;
};