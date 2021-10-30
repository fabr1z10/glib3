//
//  mesh.h
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#ifndef imesh_h
#define imesh_h

#include <monkey/bounds.h>
#include <monkey/enums.h>
#include "vertices.h"
#include <monkey/asset.h>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <monkey/itable.h>

#define INVALID_OGL_VALUE 0xFFFFFFFF

class Shader;

class IMesh : public Object {
public:
	IMesh() = default;
	IMesh(const ITab&);
    IMesh(ShaderType type) : m_vb(INVALID_OGL_VALUE), m_ib(INVALID_OGL_VALUE), m_shaderType{type} {}
    virtual ~IMesh() {}

    GLuint VertexBuffer() const { return m_vb; }
    GLuint IndexBuffer() const { return m_ib; }
    GLuint GetNumberOfIndices() { return m_nindices; }
    GLuint GetNumberOfVertices() { return m_nvertices; }
    virtual void InitAttributes() = 0;
    virtual void Setup(Shader*) {}
    virtual Bounds GetBounds() { return m_bounds; }
    void draw (Shader*, int offset, int count);
    GLenum m_primitive;
    //const glm::mat4& GetLocalTransform() const;
    std::string GetId() const;
    void SetId(const std::string&);
    ShaderType GetShaderType() const;
    glm::vec2 getKeyPoint(const std::string&) const;
    void addKeyPoint(const std::string&, glm::vec2);
    bool hasKeyPoint (const std::string&) const;
protected:
    ShaderType m_shaderType;
    //glm::mat4 m_localTransform;
    int m_scope;
    std::string m_id;
    Bounds m_bounds;
    GLuint m_nvertices;
    GLuint m_nindices;
    GLuint m_vb;
    GLuint m_ib;
    //int m_indicesCount;
    //unsigned int m_shaderMask;
    std::unordered_map<std::string, glm::vec2> m_keyPoints;
};

inline ShaderType IMesh::GetShaderType() const {
    return m_shaderType;
}

//inline const glm::mat4& IMesh::GetLocalTransform() const { return m_localTransform; }

inline std::string IMesh::GetId() const {
    return m_id;
}

inline void IMesh::SetId(const std::string& name) {
    m_id = name;
}

template<class Vertex>
Bounds ComputeBounds(std::vector<Vertex>& vertices) {
    float xm = std::numeric_limits<float>::infinity();
    float xM = -xm, yM = -xm, zM = -xm;
    float ym = xm, zm = xm;
    for (auto& v : vertices) {
        if (v.x < xm) xm = v.x; else if (v.x > xM) xM = v.x;
        if (v.y < ym) ym = v.y; else if (v.y > yM) yM = v.y;
        if (v.z < zm) zm = v.z; else if (v.z > zM) zM = v.z;
    }
    Bounds bounds;
    bounds.min = glm::vec3(xm, ym, zm);
    bounds.max = glm::vec3(xM, yM, zM);
    return bounds;
}

template<>
inline Bounds ComputeBounds<VertexText>(std::vector<VertexText>& vertices) {
    float xm = std::numeric_limits<float>::infinity();
    float xM = -xm, yM = -xm;
    float ym = xm;
    for (auto& v : vertices) {
        xm = std::min(xm, v.x);
        ym = std::min(ym, v.y);
        xM = std::max(xM, v.x);
        yM = std::max(yM, v.y);
    }
    Bounds bounds;
    bounds.min = glm::vec3(xm, ym, 0.0f);
    bounds.max = glm::vec3(xM, yM, 0.0f);
    return bounds;
}

inline glm::vec2 IMesh::getKeyPoint(const std::string & id) const {
	return m_keyPoints.at(id);
}

inline bool IMesh::hasKeyPoint(const std::string & id) const {
	return m_keyPoints.count(id) > 0;
}

inline void IMesh::addKeyPoint(const std::string & id, glm::vec2 pos) {
    m_keyPoints[id] = pos;
}

#endif /* imesh_h */
