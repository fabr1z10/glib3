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
#include <monkey/component.h>
#include <monkey/imodel.h>

// a renderer is the component responsible for rendering a model onto the screen
class Renderer : public Component {
public:
    Renderer();
    Renderer(const Renderer&);
    virtual void Draw(Shader*);
    // dynamically change the model
    virtual void SetModel(std::shared_ptr<IModel> mesh) = 0;
    IModel* GetModel();
    Bounds GetBounds() const;
    Bounds GetBounds2D() const;
    void Start() override {}
    void Update(double) override {}
    void SetParent(Entity* parent) override;
    void SetTint(glm::vec4 c);
    virtual ShaderType GetShaderType() const;
    using ParentClass = Renderer;
    //void SetMeshInfo (int offset, int count);
    //std::shared_ptr<Component> clone() const override;

    const glm::mat4& GetTransform() const;
    void SetTransform(const glm::mat4&);

protected:
    IModel* m_baseModel;
    glm::mat4 m_renderingTransform;
    glm::vec4 m_tint;
    //int m_count;
    //int m_offset;
};


inline Bounds Renderer::GetBounds() const {
    return m_baseModel->GetBounds();
}


inline IModel* Renderer::GetModel() {
    return m_baseModel;
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