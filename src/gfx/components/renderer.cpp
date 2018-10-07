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

Renderer::Renderer() : Component(), m_mesh(nullptr), m_frame(0), m_tint(1.0f), m_renderingTransform(1.0f), m_loopCount{0} {}

void Renderer::Draw(Shader* shader) {
    auto tintLoc = shader->GetUniformLocation(TINT);
    glUniform4fv(tintLoc, 1, &m_tint[0]);
    m_mesh->Draw(shader, m_animation, m_frame);
}


void Renderer::Update(double dt) {
    m_frameTime += dt;
    int frames = m_mesh->FrameCount(m_animation);
//    if (frames == 1)
  //      return;
    float duration = m_mesh->GetDuration(m_animation, m_frame);
    if (m_frameTime >= duration) {
        m_frame++;
        m_frameTime = 0;
        if (m_frame >= frames) {
            m_frame = 0;
            m_loopCount++;
        }
    }
}

void Renderer::SetAnimation(const std::string& anim) {
    // do nothing if trying to set the animation to the current one
    if (m_animation == anim)
        return;
    if (!m_mesh->HasAnimation(anim)) {
        GLIB_FAIL("Looks like animation " << anim << " does not exist for this mesh!");
    }
    m_animation = anim;
    m_frame = 0;
    m_frameTime = 0.0f;
    m_loopCount = 0;
}

bool Renderer::GetFlipX() const {
    return m_renderingTransform[0][0] < 0;
}

void Renderer::SetFlipX(bool value) {
    m_renderingTransform[0][0] = (value ? -1.0f : 1.0f) * std::fabs(m_renderingTransform[0][0]);
    //m_flipX = value;
}

void Renderer::SetScale(float scale) {
    if (m_renderingTransform[0][0]<0)
        scale = -scale;
    m_renderingTransform[0][0] = scale;
    m_renderingTransform[1][1] = fabs(scale);
    m_renderingTransform[2][2] = fabs(scale);
}