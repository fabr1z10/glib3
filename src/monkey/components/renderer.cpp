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

Renderer::Renderer() : Component(), m_baseModel(nullptr),
    m_multColor(1.0f), m_addColor(0.0f), m_renderingTransform(1.0f), m_forceZ(false), m_forcedZ(0.0f), m_texOffset(0.0f) {

}

Renderer::Renderer(const Renderer& orig) : Component(orig),
    m_multColor(orig.m_multColor), m_addColor(orig.m_addColor), m_renderingTransform(orig.m_renderingTransform), m_baseModel(orig.m_baseModel), m_texOffset(0.0f)
{
    
}



void Renderer::Draw(Shader* shader) {
    auto mcolor = shader->GetUniformLocation(MULTCOLOR);
    auto acolor = shader->GetUniformLocation(ADDCOLOR);
    if (mcolor != GL_INVALID) {
        glUniform4fv(mcolor, 1, &m_multColor[0]);
    }
    if (acolor != GL_INVALID) {
        glUniform4fv(acolor, 1, &m_addColor[0]);
    }
//    auto fz = shader->GetUniformLocation(FORCEZ);
//	auto fzv = shader->GetUniformLocation(FORCEDZ);
//    if (fz != GL_INVALID) {
//    	glUniform1i(fz, m_forceZ ? 1 : 0);
//    	glUniform1f(fzv, m_forcedZ);
//    }

    auto to = shader->GetUniformLocation(TEXOFFSET);
    glUniform2fv (to, 1, &m_texOffset[0]);
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

