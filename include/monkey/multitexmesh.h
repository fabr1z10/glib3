#pragma once

#include <monkey/mesh.h>
#include <monkey/engine.h>
#include <monkey/math/earcut.h>


struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

template <typename T>
class MultiTexMesh : public Mesh<T> {
public:
    MultiTexMesh() = default;

    MultiTexMesh(ShaderType type, GLenum prim, const std::vector<Texture>& textures) : Mesh<T>(type), m_textures(textures) {
        this->m_primitive = prim;
    }

    void Setup(Shader* shader) override {
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for(unsigned int i = 0; i < m_textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = m_textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if(name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if(name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader->getProgId(), (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
        }

    }
private:
    std::vector<Texture> m_textures;
};

