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
    Bounds3D GetBounds() const;
    void Start() override {}
    void Update(double) override;
    void SetAnimation(const std::string&);
    void SetTint(glm::vec4& c);
    ShaderType GetShaderType() const { return m_mesh->GetShaderType(); }
    using ParentClass = Renderer;
private:
    std::shared_ptr<IMesh> m_mesh;
    bool m_visible;
    std::string m_animation;
    int m_frame;
    double m_frameTime;
    glm::vec4 m_tint;
};

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

inline void Renderer::SetTint(glm::vec4& color) {
    m_tint = color;
}


#endif /* renderer_h */
