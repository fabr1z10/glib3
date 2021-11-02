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
#include <monkey/assets/model.h>

enum Blend {
	DEFAULT=0, ADD, SUB
};

// a renderer is the component responsible for rendering a model onto the screen

class __attribute__ ((visibility ("default"))) Renderer : public Component {
public:
    Renderer() = default;
    //Renderer(const Renderer&);
    Renderer(std::shared_ptr<Model>);
    Renderer(const ITab& t);
    ~ Renderer() override = default;
    void init(Shader*);
    virtual void Draw(Shader*);
    void post();
    // dynamically change the model
    void setModel(std::shared_ptr<Model>);
    Model* GetModel();
    Bounds GetBounds() const;
    Bounds GetBounds2D() const;
    void Start() override {}
    void Update(double) override {}
    void SetParent(Entity* parent) override;
    void setMultColor(glm::vec4 c);
    void setAddColor(glm::vec4 c);
    void setTextureOffset (glm::vec2& offset);
    void setForcedZ(float);
    //virtual ShaderType GetShaderType() const;
    using ParentClass = Renderer;
    //void SetMeshInfo (int offset, int count);
    //std::shared_ptr<Component> clone() const override;

    const glm::mat4& GetTransform() const;
    void SetTransform(const glm::mat4&);
	void setBlendMode (Blend);
	void setDepthFunc (GLenum);
protected:
    std::shared_ptr<Model> m_model;
    glm::mat4 m_renderingTransform;
    glm::vec4 m_multColor;
    glm::vec4 m_addColor;
    bool m_forceZ;
    float m_forcedZ;
    glm::vec2 m_texOffset;
    Blend m_blend;
    GLenum m_depth;
    //int m_count;
    //int m_offset;
};


inline Bounds Renderer::GetBounds() const {
    return m_model->getBounds();
}


inline Model* Renderer::GetModel() {
    return m_model.get();
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

inline void Renderer::setModel(std::shared_ptr<Model> model) {
    m_model = model;
}


#endif /* renderer_h */
