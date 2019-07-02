//
//  renderer.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#include <gfx/components/renderer.h>
#include <gfx/shader.h>
#include <gfx/error.h>
#include <gfx/entity.h>
#include <iostream>

Renderer::Renderer() : Component(), m_model(nullptr), m_tint(1.0f), m_offset(0), m_count(0) {}

Renderer::Renderer(const Renderer& orig) : Component(orig),
m_model(orig.m_model), m_tint(orig.m_tint), m_offset(orig.m_offset), m_count(orig.m_count) {
    
}

std::shared_ptr<Component> Renderer::clone() const {
    return std::make_shared<Renderer>(Renderer(*this));
}

void Renderer::Draw(Shader* shader) {
    auto tintLoc = shader->GetUniformLocation(TINT);
    if (tintLoc != GL_INVALID)
        glUniform4fv(tintLoc, 1, &m_tint[0]);
    m_model->Draw(shader, m_offset, m_count);
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

