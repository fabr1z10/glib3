//
//  mesh.h
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#ifndef mesh_h
#define mesh_h

#include "gfx/bounds.h"
#include "gfx/enums.h"
#include "vertices.h"
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

#define INVALID_OGL_VALUE 0xFFFFFFFF

class Shader;



struct FrameInfo {
    int offset, count;
    float duration;
};

struct AnimInfo {
public:
    AnimInfo (bool loop) : loop(loop) {}
    size_t getFrameCount () const {
        return frameInfo.size();
    }
    bool isLoop() const {
        return loop;
    }
    void AddFrameInfo(FrameInfo& f) {
        frameInfo.emplace_back(f);
    }
    int getCount(int frame) const {
        return frameInfo[frame].count;
    }
    int getOffset(int frame) const {
        return frameInfo[frame].offset;
    }
    float getDuration (int frame) const {
        return frameInfo[frame].duration;
    }
private:
    bool loop;
    std::vector<FrameInfo> frameInfo;

};

// abstract class for mesh
class IMesh {
public:
    IMesh(ShaderType type) : m_vb(INVALID_OGL_VALUE), m_ib(INVALID_OGL_VALUE), m_offset{0}, m_shaderType{type}, m_localTransform{glm::mat4(1.0f)} {}
    virtual ~IMesh() {}
    GLuint VertexBuffer() const { return m_vb; }
    GLuint IndexBuffer() const { return m_ib; }
    GLuint GetNumberOfIndices() { return m_nindices; }
    GLuint GetNumberOfVertices() { return m_nvertices; }
    /// get the number of animations in the mesh
    int AnimationCount() const;

    const AnimInfo& GetAnimInfo(const std::string&);
    /// get the number of frames int the given animation
    //int FrameCount(const std::string& anim) const;
    /// get the duration of a given frame of a given animation
    //float GetDuration(const std::string& anim, int frame) const;
    bool HasAnimation(const std::string& anim) {
        return m_animInfo.find(anim) != m_animInfo.end();
    }
    virtual void InitAttributes() = 0;
    virtual void Setup(Shader*, const std::string&, int) {}
    virtual Bounds3D GetBounds() { return m_bounds; }
    virtual int UpdateFrame(int anim, int frame, float time) { return frame; }
    virtual void Draw(Shader*, const std::string&, int frame = 0);

    GLenum m_primitive;
    const glm::mat4& GetLocalTransform() const;
    void SetScope(int);
    int GetScope() const;
    ShaderType GetShaderType() const { return m_shaderType; }
    std::string GetDefaultAnimation() const { return m_defaultAnimation; }
    std::string GetId() const;
    void SetId(const std::string&);
protected:
    ShaderType m_shaderType;
    glm::mat4 m_localTransform;
    int m_scope;
    //int m_animations;
    std::unordered_map <std::string, AnimInfo > m_animInfo;
    std::string m_defaultAnimation;
    std::string m_id;
    Bounds3D m_bounds;
    GLsizei m_count;
    GLint m_offset;
    GLuint m_nvertices;
    GLuint m_nindices;
    GLuint m_vb;
    GLuint m_ib;
    unsigned int m_shaderMask;
    
};

inline const glm::mat4& IMesh::GetLocalTransform() const { return m_localTransform; }
inline void IMesh::SetScope(int value) { m_scope = value; }
inline int IMesh::GetScope() const { return m_scope; }

inline int IMesh::AnimationCount() const { return m_animInfo.size(); }
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

template<class Vertex>
class Mesh : public IMesh {
public:
    Mesh(ShaderType type) : IMesh(type) {}
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
        Init(vertices, indices);
    }
    ~Mesh() {
        if (m_vb != INVALID_OGL_VALUE)
            glDeleteBuffers(1, &m_vb);
        if (m_ib != INVALID_OGL_VALUE)
            glDeleteBuffers(1, &m_ib);
    }
    
    void Init(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
        m_nvertices = vertices.size();
        m_nindices = indices.size();
        glGenBuffers(1, &m_vb);
        glGenBuffers(1, &m_ib);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vb);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
        m_count = GetNumberOfIndices();
        m_bounds = ComputeBounds(vertices);
    }
    
    virtual void InitAttributes() {
        Vertex::InitAttributes();
    }
    
};

#endif /* mesh_h */
