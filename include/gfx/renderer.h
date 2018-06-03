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

class Renderer : public Component {
public:
    Renderer();
    void Draw(Shader*);
    bool isVisible() const;
    const glm::mat4& GetTransform() const;
    void SetMesh(std::shared_ptr<IMesh> mesh);
    IMesh* GetMesh();
    Bounds3D GetBounds() const;
    void Start() override {}
    void Update(double) override;
    void SetAnimation(const std::string&);
    void SetTint(glm::vec4 c);
    ShaderType GetShaderType() const { return m_mesh->GetShaderType(); }
    using ParentClass = Renderer;
    void SetFlipX(bool);
    bool GetFlipX() const;
    const glm::mat4& GetRenderingTransform() const;
    void SetRenderingTransform (glm::mat4 m);
private:
    //bool m_flipX;
    glm::mat4 m_renderingTransform;
    std::shared_ptr<IMesh> m_mesh;
    bool m_visible;
    std::string m_animation;
    int m_frame;
    double m_frameTime;
    glm::vec4 m_tint;
};

inline const glm::mat4& Renderer::GetRenderingTransform() const{
    return m_renderingTransform;
}

inline void Renderer::SetRenderingTransform (glm::mat4 m) {
    m_renderingTransform = m;
}

inline Bounds3D Renderer::GetBounds() const {
    return m_mesh->GetBounds();
}

inline const glm::mat4& Renderer::GetTransform() const {
    return m_mesh->GetLocalTransform();
}

inline bool Renderer::isVisible() const {
    return m_visible;
}

inline void Renderer::SetMesh(std::shared_ptr<IMesh> mesh) {
    m_mesh = mesh;
}

inline IMesh* Renderer::GetMesh() {
    return m_mesh.get();
}

inline void Renderer::SetTint(glm::vec4 color) {
    m_tint = color;
}


#endif /* renderer_h */
