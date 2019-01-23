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

Renderer::Renderer() : Component(), m_mesh(nullptr),
                       m_frame(0), m_frameTime(0.0), m_tint(1.0f), m_loopCount{0}, m_currentAnim(nullptr) {}

void Renderer::Draw(Shader* shader) {
    auto tintLoc = shader->GetUniformLocation(TINT);
    if (tintLoc != -1)
        glUniform4fv(tintLoc, 1, &m_tint[0]);
    m_mesh->Draw(shader, m_animation, m_frame);
}

void Renderer::AdvanceFrame(int m) {
    m_frame += m;
    int n = m_currentAnim->getFrameCount();
    if (m_frame >= n) {
        m_frame = 0;
    } else if (m_frame < 0) {

        m_frame = n-1;
    }
    std::cout << "new frame; " << m_frame << "\n";

}

void Renderer::SetFrame(int frame) {
    if (m_frame != frame) {
        m_frame = frame;
        m_frameTime = 0.0;

        size_t frames = m_currentAnim->getFrameCount();
        if (m_frame < 0) {
            m_frame = frames-1;
        } else if (m_frame >= frames) {
            m_frame = m_currentAnim->isLoop() ? 0 : frames-1;
            m_loopCount++;
        }
        for (auto& h : m_frameChangeHandlers) {
            h->Handle(m_animation, m_frame);
        }
    }
}

void Renderer::Update(double dt) {
    if (m_currentAnim != nullptr) {
        m_frameTime += dt;
        float duration = m_currentAnim->getDuration(m_frame);
        if (m_frameTime >= duration) {

            float dx = m_frameTime-duration;
            SetFrame(m_frame + 1);
            m_frameTime=dx;
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
    m_currentAnim = &m_mesh->GetAnimInfo(m_animation);
    m_loopCount = 0;
}

//void Renderer::SetScale(float scale) {
//    if (m_renderingTransform[0][0]<0)
//        scale = -scale;
//    m_renderingTransform[0][0] = scale;
//    m_renderingTransform[1][1] = fabs(scale);
//    m_renderingTransform[2][2] = fabs(scale);
//}

void Renderer::SetParent(Entity *parent) {
    Component::SetParent(parent);
    for (auto& fc : m_frameChangeHandlers)
        fc->SetEntity(parent);
}

void Renderer::AddFrameChangeHandler (std::unique_ptr<IFrameChangeHandler> fc) {
    m_frameChangeHandlers.push_back(std::move(fc));
}