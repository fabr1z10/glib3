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
#include "gfx/imodel.h"

// a renderer is the component responsible for rendering a model onto the screen
class Renderer : public Component {
public:
    Renderer();
    Renderer(const Renderer&);
    virtual void Draw(Shader*);
    void SetModel(std::shared_ptr<IModel> mesh);
    IModel* GetModel();
    Bounds GetBounds() const;
    Bounds GetBounds2D() const;
    void Start() override {}
    void Update(double) override {}
    void SetParent(Entity* parent) override;
    void SetTint(glm::vec4 c);
    ShaderType GetShaderType() const { return (m_model == nullptr ? ShaderType::NONE : m_model->GetShaderType()); }
    using ParentClass = Renderer;
    //void SetMeshInfo (int offset, int count);
    std::shared_ptr<Component> clone() const override;

    const glm::mat4& GetTransform() const;
    void SetTransform(const glm::mat4&);

private:
    glm::mat4 m_renderingTransform;
    std::shared_ptr<IModel> m_model;
    glm::vec4 m_tint;
    //int m_count;
    //int m_offset;
};





inline Bounds Renderer::GetBounds() const {
    return m_model->GetBounds();
}


//inline bool Renderer::isVisible() const {
//    return m_visible;
//}

inline void Renderer::SetModel(std::shared_ptr<IModel> mesh) {
    m_model = mesh;
}

inline IModel* Renderer::GetModel() {
    return m_model.get();
}

inline void Renderer::SetTint(glm::vec4 color) {
    m_tint = color;
}


//
//inline void Renderer::SetMeshInfo (int offset, int count) {
//    m_offset = offset;
//    m_count = count;
//}


#endif /* renderer_h */
