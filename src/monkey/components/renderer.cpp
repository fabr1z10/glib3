//
//  renderer.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#include <monkey/components/renderer.h>
#include <monkey/shader.h>
#include <monkey/error.h>
#include <monkey/entity.h>
#include <iostream>

Renderer::Renderer() : Component(), m_baseModel(nullptr), m_tint(1.0f), m_renderingTransform(1.0f) {

}

Renderer::Renderer(const Renderer& orig) : Component(orig), m_tint(orig.m_tint), m_renderingTransform(orig.m_renderingTransform), m_baseModel(orig.m_baseModel) {
    
}



void Renderer::Draw(Shader* shader) {
    auto tintLoc = shader->GetUniformLocation(TINT);
    if (tintLoc != GL_INVALID)
        glUniform4fv(tintLoc, 1, &m_tint[0]);
    //m_model->Draw(shader, m_offset, m_count);
}

const glm::mat4& Renderer::GetTransform() const {
    return m_renderingTransform;
}

void Renderer::SetTransform(const glm::mat4& t) {
    m_renderingTransform = t;
}

ShaderType Renderer::GetShaderType() const {
    return (m_baseModel == nullptr ? ShaderType::NONE : m_baseModel->GetShaderType());
}

Bounds Renderer::GetBounds2D() const {
    Bounds b = GetBounds();

    b.Transform(m_renderingTransform);
    return b;
}

//void Renderer::AdvanceFrame(int m) {
//    m_frame += m;
//    int n = m_currentAnim->getFrameCount();
//    if (m_frame >= n) {
//        m_frame = 0;
//    } else if (m_frame < 0) {
//
//        m_frame = n-1;
//    }
//    std::cout << "new frame; " << m_frame << "\n";
//
//}







//void Renderer::SetScale(float scale) {
//    if (m_renderingTransform[0][0]<0)
//        scale = -scale;
//    m_renderingTransform[0][0] = scale;
//    m_renderingTransform[1][1] = fabs(scale);
//    m_renderingTransform[2][2] = fabs(scale);
//}

void Renderer::SetParent(Entity *parent) {
    Component::SetParent(parent);

}
