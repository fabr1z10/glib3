#include <monkey/model/model3d.h>



Model3D::Model3D(const ITab & t) {

}

void Model3D::loadModel(const std::string &path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        GLIB_FAIL("ERROR::ASSIMP::" << import.GetErrorString());
    }
    //directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model3D::draw(Shader*, int, int) {

}

Bounds Model3D::GetBounds() const {
    return Bounds();
}
ShaderType Model3D::GetShaderType() const {
    return TEXTURE_SHADER_UNLIT;
}

std::vector<std::string> Model3D::GetAnimations() const {
    return std::vector<std::string>();
}

std::string Model3D::GetDefaultAnimation() const {
    return "";
}


void Model3D::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        // TODO meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}