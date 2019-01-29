//
//  renderer.h
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#ifndef renderer_h
#define renderer_h

#include <memory>
#include "gfx/component.h"
#include "gfx/mesh.h"
#include "gfx/framechangehandler.h"

class Renderer : public Component {
public:
    Renderer();
    void Draw(Shader*);
    const glm::mat4& GetTransform() const;
    void SetMesh(std::shared_ptr<IMesh> mesh);
    IMesh* GetMesh();
    Bounds3D GetBounds() const;
    void Start() override {}
    void Update(double) override {}
    void SetParent(Entity* parent) override;
    void SetTint(glm::vec4 c);
    ShaderType GetShaderType() const { return (m_mesh == nullptr ? ShaderType::NONE : m_mesh->GetShaderType()); }
    using ParentClass = Renderer;
    const glm::mat4& GetRenderingTransform() const;
    void SetMeshInfo (int offset, int count);
private:
    std::shared_ptr<IMesh> m_mesh;
    glm::vec4 m_tint;
    int m_count;
    int m_offset;
};




inline const glm::mat4& Renderer::GetRenderingTransform() const{
    return m_mesh->GetLocalTransform();
}


inline Bounds3D Renderer::GetBounds() const {
    return m_mesh->GetBounds();
}

inline const glm::mat4& Renderer::GetTransform() const {
    return m_mesh->GetLocalTransform();
}

//inline bool Renderer::isVisible() const {
//    return m_visible;
//}

inline void Renderer::SetMesh(std::shared_ptr<IMesh> mesh) {
    m_mesh = mesh;
}

inline IMesh* Renderer::GetMesh() {
    return m_mesh.get();
}

inline void Renderer::SetTint(glm::vec4 color) {
    m_tint = color;
}



inline void Renderer::SetMeshInfo (int offset, int count) {
    m_offset = offset;
    m_count = count;
}


#endif /* renderer_h */
