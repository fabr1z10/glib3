#ifdef USE_ASSIMP

#include <monkey/model/model3d.h>
#include <monkey/engine.h>


Model3D::Model3D(const ITab & t) {
    auto model = t.get<std::string>("image");
    m_baseDirectory = model.substr(0,model.rfind('/')+1);
    std::string file = Engine::get().GetGameDirectory() + model;
    std::cout << file << "\n";
    loadModel(file);
    exit(1);
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

void Model3D::draw(Shader* shader, int offset, int count) {
    for (const auto& mesh : m_meshes) {
        mesh->Draw(shader, offset, count);
    }
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
        m_meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

std::shared_ptr<IMesh> Model3D::processMesh(aiMesh* mesh, const aiScene* scene) {
    // convert a assimp mesh into an own  mesh
    std::vector<Vertex3DN> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex3DN vertex;
        vertex.x = mesh->mVertices[i].x;
        vertex.y = mesh->mVertices[i].y;
        vertex.z = mesh->mVertices[i].z;
        // normals
        if (mesh->HasNormals()) {
            vertex.nx = mesh->mNormals[i].x;
            vertex.ny = mesh->mNormals[i].y;
            vertex.nz = mesh->mNormals[i].z;
        }
        if (mesh->mTextureCoords[0]) { // does the mesh contain texture coords?
            vertex.s = mesh->mTextureCoords[0][i].x;
            vertex.t = mesh->mTextureCoords[0][i].y;
            // TODO tangent and bitangent
        }
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number raning from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");

    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    return std::make_shared<MultiTexMesh<Vertex3DN>>(ShaderType::TEXTURE_SHADER_LIGHT, GL_TRIANGLES, textures);



}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
std::vector<Texture> Model3D::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        std::string full_path = m_baseDirectory + std::string(str.C_Str());
        auto tex = Engine::get().GetAssetManager().GetTex(full_path);
        Texture texture;
        texture.type = typeName;
        texture.id = tex->GetTexId();
    }
    return textures;
}

#endif