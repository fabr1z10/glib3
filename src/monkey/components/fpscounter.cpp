#include <monkey/components/fpscounter.h>
#include <GLFW/glfw3.h>
#include <monkey/components/renderer.h>
#include <monkey/entity.h>

FPSCounter::FPSCounter() : Component(), m_frameCount(0), m_frameStart(0.0), m_textMesh(nullptr) {}

FPSCounter::FPSCounter(const FPSCounter& orig) : Component(orig) {}

FPSCounter::FPSCounter(const ITable & t) : FPSCounter() {

}

std::shared_ptr<Component> FPSCounter::clone() const {
    return std::make_shared<FPSCounter>(FPSCounter(*this));
}

void FPSCounter::Start() {

    m_frameCount = 0;
    m_frameStart = 0.0;
    auto* r = m_entity->GetComponent<Renderer>();
    m_textMesh = dynamic_cast<TextModel*>(r->GetModel());
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
        m_textMesh->SetText (std::to_string(static_cast<int>(fps)));
        m_frameCount = 0;
    }
}
