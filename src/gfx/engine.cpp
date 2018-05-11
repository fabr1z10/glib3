#include "gfx/engine.h"
#include <gfx/error.h>
#include "gfx/app.h"


void Engine::Init(const EngineConfig& config) {
    m_window = config.window;
    m_frameTime = 1.0 / config.frameRate;
    m_running = false;
    m_deviceSize = glm::vec2(config.deviceWidth, config.deviceHeight);
    // initialize shaders
    AddShader (ShaderFactory::GetTextureShader());
    AddShader (ShaderFactory::GetColorShader());



}

void Engine::MainLoop() {
    if (m_sceneFactory == nullptr)
        GLIB_FAIL("Scene factory has not been set.")

    if (!glfwWindowShouldClose(m_window)) {

        // load the scene
        // scene is an entity (often a container entity)
        m_scene = m_sceneFactory->Create();
        
        // start the scene (initialize components)
        for (auto iter = m_scene->begin(); iter != m_scene->end(); ++iter) {
            iter->Start();
        }
        
        m_running = true;
        // run the scene
        while (!glfwWindowShouldClose(m_window)) {
            double currentTime = glfwGetTime();
            if (currentTime - m_timeLastUpdate >= m_frameTime) {
                m_timeLastUpdate = currentTime;
                
                // update all active components
                for (auto iter = m_scene->begin(); iter != m_scene->end(); ++iter) {
                    iter->Update(m_frameTime);
                }
                
                
                glClearColor(0.0f,0.0f,0.3f,1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glfwSwapBuffers(m_window);
                glfwPollEvents();
            }
        }
        
        m_running = false;
    }
}

void Engine::WindowResizeCallback(GLFWwindow* win, int width, int height) {
    // notify cameras
    for (auto& listener : Engine::get().m_resizeListeners)
        listener->Notify(width, height);

}

void Engine::RegisterToWindowResizeEvent(WindowResizeListener* listener) {
    m_resizeListeners.insert(listener);
}

void Engine::UnregisterToWindowResizeEvent(WindowResizeListener* listener) {
    m_resizeListeners.erase(listener);
}

Engine::~Engine() {
    glfwTerminate();
}