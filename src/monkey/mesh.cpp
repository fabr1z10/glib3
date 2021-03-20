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

IMesh::IMesh(const YAML::Node& t) {

	m_shaderType = static_cast<ShaderType>(t["shader"].as<int>(0));
	m_primitive = t["primitive"].as<GLenum>(GL_TRIANGLES);
	// read keypoints
	if (t["key_points"]) {
	    for (auto kp : t["key_points"]) {
	        auto id = kp.first.as<std::string>();
	        auto pos = YamlWrapper::as<glm::vec2>(kp.second);
	        m_keyPoints[id] = pos;
	    }
	}
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
