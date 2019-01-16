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

Renderer::Renderer() : Component(), m_mesh(nullptr), m_frame(0), m_tint(1.0f), m_renderingTransform(1.0f), m_loopCount{0} {}

void Renderer::Draw(Shader* shader) {
    auto tintLoc = shader->GetUniformLocation(TINT);
    if (tintLoc != -1)
        glUniform4fv(tintLoc, 1, &m_tint[0]);
    m_mesh->Draw(shader, m_animation, m_frame);
}

void Renderer::SetFrame(int frame) {
    if (m_frame != frame) {
        m_frame = frame;
        m_frameTime = 0.0;
        int frames = m_mesh->FrameCount(m_animation);
        if (m_frame >= frames) {
            m_frame = 0;
            m_loopCount++;
        }
        for (auto& h : m_frameChangeHandlers) {
            h->Handle(m_animation, m_frame);
        }
    }
}

void Renderer::Update(double dt) {
    if (m_mesh != nullptr) {
        m_frameTime += dt;
        float duration = m_mesh->GetDuration(m_animation, m_frame);
        if (m_frameTime >= duration) {
            SetFrame(m_frame + 1);
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
    SetFrame (0);
    m_loopCount = 0;
}

void Renderer::SetScale(float scale) {
    if (m_renderingTransform[0][0]<0)
        scale = -scale;
    m_renderingTransform[0][0] = scale;
    m_renderingTransform[1][1] = fabs(scale);
    m_renderingTransform[2][2] = fabs(scale);
}

void Renderer::SetParent(Entity *parent) {
    Component::SetParent(parent);
    for (auto& fc : m_frameChangeHandlers)
        fc->SetEntity(parent);
}

void Renderer::AddFrameChangeHandler (std::unique_ptr<IFrameChangeHandler> fc) {
    m_frameChangeHandlers.push_back(std::move(fc));
}