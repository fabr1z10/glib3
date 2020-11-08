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
#include <monkey/assets/imodel.h>

// a renderer is the component responsible for rendering a model onto the screen
class Renderer : public Component {
public:
    Renderer();
    Renderer(const Renderer&);
    ~ Renderer() override = default;
    virtual void Draw(Shader*);
    // dynamically change the model
    virtual void SetModel(std::shared_ptr<IModel> mesh) = 0;
    IModel* GetModel();
    Bounds GetBounds() const;
    Bounds GetBounds2D() const;
    void Start() override {}
    void Update(double) override {}
    void SetParent(Entity* parent) override;
    void setMultColor(glm::vec4 c);
    void setAddColor(glm::vec4 c);
    void setTextureOffset (glm::vec2& offset);
    void setForcedZ(float);
    virtual ShaderType GetShaderType() const;
    using ParentClass = Renderer;
    //void SetMeshInfo (int offset, int count);
    //std::shared_ptr<Component> clone() const override;

    const glm::mat4& GetTransform() const;
    void SetTransform(const glm::mat4&);

protected:
    IModel* m_baseModel;
    glm::mat4 m_renderingTransform;
    glm::vec4 m_multColor;
    glm::vec4 m_addColor;
    bool m_forceZ;
    float m_forcedZ;
    glm::vec2 m_texOffset;
    //int m_count;
    //int m_offset;
};


inline Bounds Renderer::GetBounds() const {
    return m_baseModel->GetBounds();
}


inline IModel* Renderer::GetModel() {
    return m_baseModel;
}

inline void Renderer::setMultColor(glm::vec4 c) {
    m_multColor = c;
}

inline void Renderer::setAddColor(glm::vec4 c) {
    m_addColor = c;
}

inline void Renderer::setTextureOffset(glm::vec2 &offset) {
    m_texOffset = offset;
}

inline void Renderer::setForcedZ(float value) {
	m_forcedZ = value;
	m_forceZ = true;
}
//
//inline void Renderer::SetMeshInfo (int offset, int count) {
//    m_offset = offset;
//    m_count = count;
//}


#endif /* renderer_h */
