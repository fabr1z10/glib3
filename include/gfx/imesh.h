//
//  mesh.h
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#ifndef imesh_h
#define imesh_h

#include "gfx/bounds.h"
#include "gfx/enums.h"
#include "vertices.h"
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

#define INVALID_OGL_VALUE 0xFFFFFFFF

class Shader;



//struct FrameInfo {
//    int offset, count;
//    float duration;
//};
//
//struct AnimInfo {
//public:
//    AnimInfo (bool loop) : loop(loop) {}
//    size_t getFrameCount () const {
//        return frameInfo.size();
//    }
//    bool isLoop() const {
//        return loop;
//    }
//    void AddFrameInfo(FrameInfo& f) {
//        frameInfo.emplace_back(f);
//    }
//    int getCount(int frame) const {
//        return frameInfo[frame].count;
//    }
//    int getOffset(int frame) const {
//        return frameInfo[frame].offset;
//    }
//    float getDuration (int frame) const {
//        return frameInfo[frame].duration;
//    }
//private:
//    bool loop;
//    std::vector<FrameInfo> frameInfo;
//
//};

// abstract class for mesh
class IMesh {
public:
    IMesh(ShaderType type) : m_vb(INVALID_OGL_VALUE), m_ib(INVALID_OGL_VALUE), m_shaderType{type}, m_localTransform{glm::mat4(1.0f)} {}
    virtual ~IMesh() {}
    GLuint VertexBuffer() const { return m_vb; }
    GLuint IndexBuffer() const { return m_ib; }
    GLuint GetNumberOfIndices() { return m_nindices; }
    GLuint GetNumberOfVertices() { return m_nvertices; }
    virtual void InitAttributes() = 0;
    virtual void Setup(Shader*) {}
    virtual Bounds3D GetBounds() { return m_bounds; }
    void Draw (Shader*, int offset, int count);
    GLenum m_primitive;
    const glm::mat4& GetLocalTransform() const;
    ShaderType GetShaderType() const;
    std::string GetId() const;
    void SetId(const std::string&);
protected:
    ShaderType m_shaderType;
    glm::mat4 m_localTransform;
    int m_scope;
    std::string m_id;
    Bounds3D m_bounds;
    GLuint m_nvertices;
    GLuint m_nindices;
    GLuint m_vb;
    GLuint m_ib;
    int m_indicesCount;
    unsigned int m_shaderMask;
};

inline const glm::mat4& IMesh::GetLocalTransform() const { return m_localTransform; }

inline std::string IMesh::GetId() const {
    return m_id;
}

inline void IMesh::SetId(const std::string& name) {
    m_id = name;
}

template<class Vertex>
Bounds3D ComputeBounds(std::vector<Vertex>& vertices) {
    float xm = std::numeric_limits<float>::infinity();
    float xM = -xm, yM = -xm, zM = -xm;
    float ym = xm, zm = xm;
    for (auto& v : vertices) {
        xm = std::min(xm, v.x);
        ym = std::min(ym, v.y);
        zm = std::min(zm, v.z);
        xM = std::max(xM, v.x);
        yM = std::max(yM, v.y);
        zM = std::max(zM, v.z);
    }
    Bounds3D bounds;
    bounds.min = glm::vec3(xm, ym, zm);
    bounds.max = glm::vec3(xM, yM, zM);
    return bounds;
}

template<>
inline Bounds3D ComputeBounds<VertexText>(std::vector<VertexText>& vertices) {
    float xm = std::numeric_limits<float>::infinity();
    float xM = -xm, yM = -xm;
    float ym = xm;
    for (auto& v : vertices) {
        xm = std::min(xm, v.x);
        ym = std::min(ym, v.y);
        xM = std::max(xM, v.x);
        yM = std::max(yM, v.y);
    }
    Bounds3D bounds;
    bounds.min = glm::vec3(xm, ym, 0.0f);
    bounds.max = glm::vec3(xM, yM, 0.0f);
    return bounds;
}

inline ShaderType IMesh::GetShaderType() const {
    return m_shaderType;
}


#endif /* imesh_h */
