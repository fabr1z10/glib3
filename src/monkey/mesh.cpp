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

IMesh::IMesh(const ITab& t) {

	m_shaderType = static_cast<ShaderType>(t.get<int>("shader", 0));
	m_primitive = t.get<GLenum>("primitive", GL_TRIANGLES);
	// read keypoints
	t.foreach("key_points", [&] (const std::string& id, const ITab& t) {
        auto pos = t.as<glm::vec2>();
        m_keyPoints[id] = pos;
	});
}

void IMesh::Draw(Shader* shader, int offset, int count) {
    if (count == 0) count = m_nindices;
    glBindBuffer(GL_ARRAY_BUFFER, m_vb);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);
    Setup(shader);
    InitAttributes();
    glDrawElements(m_primitive, count, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * offset));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


//const AnimInfo& IMesh::GetAnimInfo(const std::string& id) {
//    if (m_animInfo.count(id) == 0) {
//        GLIB_FAIL("Unknown animation " << id);
//    }
//    return m_animInfo.at(id);
//}
