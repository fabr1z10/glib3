//
//  renderer.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#include <gfx/renderer.h>
#include <gfx/shader.h>

Renderer::Renderer() : m_mesh(nullptr), m_visible(true), m_frame(0), m_tint(1.0f) {}

void Renderer::Draw(Shader* shader) {
    auto tintLoc = shader->GetUniformLocation(TINT);
    glUniform4fv(tintLoc, 1, &m_tint[0]);
    m_mesh->Draw(shader, m_animation, m_frame);
}


void Renderer::Update(double dt) {
    m_frameTime += dt;
    int frames = m_mesh->FrameCount(m_animation);
    if (frames == 1)
        return;
    float duration = m_mesh->GetDuration(m_animation, m_frame);
    if (m_frameTime >= duration) {
        m_frame++;
        m_frameTime = 0;
        if (m_frame >= frames)
            m_frame = 0;
    }
}