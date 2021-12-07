//
//  mesh.cpp
//  glib
//
//  Created by Fabrizio Venturini on 06/05/2018.
//
//

#include <monkey/mesh.h>
#include <monkey/shader.h>
#include <monkey/error.h>

std::array<std::string,3> IMesh::g_texTypeStr = {"texture_diffuse", "texture_specular", "texture_normal"};


IMesh::IMesh(const ITab& t) {

	m_shaderType = static_cast<ShaderType>(t.get<int>("shader", 0));
	m_primitive = t.get<GLenum>("primitive", GL_TRIANGLES);

}

void IMesh::draw(Shader* shader, int offset, int count) {
    if (count == 0) count = m_nindices;
    glBindBuffer(GL_ARRAY_BUFFER, m_vb);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);
    Setup(shader);
    shader->initVertexAttributes();

    glDrawElements(m_primitive, count, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * offset));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IMesh::Setup(Shader * shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    std::array<unsigned int, IMesh::g_texTypeStr.size()> nr;

    nr.fill(1);
    for(unsigned int i = 0; i < m_textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string name = g_texTypeStr[m_textures[i].type];
        name += std::to_string(nr[m_textures[i].type]++);
        shader->setInt(name, i);

        //shader.setFloat(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }
    //shader->initVertexAttributes();

}

//const AnimInfo& IMesh::GetAnimInfo(const std::string& id) {
//    if (m_animInfo.count(id) == 0) {
//        GLIB_FAIL("Unknown animation " << id);
//    }
//    return m_animInfo.at(id);
//}
