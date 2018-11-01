#include <gfx/components/fpscounter.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gfx/components/renderer.h>
#include <gfx/entity.h>

FPSCounter::FPSCounter() : Component() {}

void FPSCounter::Start() {

    m_frameCount = 0;
    m_frameStart = 0.0;
    Renderer* r = m_entity->GetComponent<Renderer>();
    m_textMesh = dynamic_cast<TextMesh*>(r->GetMesh());
}

void FPSCounter::Update(double) {

    // count fps
    m_frameCount++;
    if (m_frameCount >= 10) {
        double totalTime = glfwGetTime() - m_frameStart;
        m_frameStart = glfwGetTime();
        double fps = std::round(m_frameCount / totalTime);
        //m_assetManager.GetVariable("_fps")->SetInt(static_cast<int>(fps));
        //m_vars.Get("_fps")->Set(static_cast<int>(fps));
        m_textMesh->UpdateText(std::to_string(static_cast<int>(fps)));
        m_frameCount = 0;
    }
}