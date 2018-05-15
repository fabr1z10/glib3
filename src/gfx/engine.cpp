#include "gfx/engine.h"
#include <gfx/error.h>


extern GLFWwindow* window;

void Engine::Init(const EngineConfig& config) {
    m_window = config.window;
    m_frameTime = 1.0 / config.frameRate;
    m_running = false;
    m_deviceSize = glm::vec2(config.deviceWidth, config.deviceHeight);
    // initialize shaders
    AddShader (ShaderFactory::GetTextureShader());
    AddShader (ShaderFactory::GetColorShader());
    if (config.enableMouse) {
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetCursorPosCallback(window, cursor_pos_callback);
    }

    if (config.enableKeyboard) {
        glfwSetKeyCallback(window, key_callback );
    }

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

                // remove all entities scheduled for removal
                if (!m_garbage.empty()) {
                    for (auto &g : m_garbage) {
                        auto parent = g->GetParent();
                        parent->Remove(g);
                    }
                    m_garbage.clear();
                }


                glClearColor(0.0f,0.0f,0.3f,1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                // update all active components
                for (auto iter = m_scene->begin(); iter != m_scene->end(); ++iter) {
                    iter->Update(m_frameTime);
                }
                
                

                glfwSwapBuffers(m_window);
                glfwPollEvents();
            }
        }
        m_scene = nullptr;
        m_running = false;
    }
}

void Engine::WindowResizeCallback(GLFWwindow* win, int width, int height) {
    // notify cameras
    for (auto& listener : Engine::get().m_resizeListeners)
        listener->Notify(width, height);

}

void Engine::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
    for (auto& listener : Engine::get().m_mouseListeners)
        listener->MouseButtonCallback(win, button, action, mods);
}

void Engine::cursor_pos_callback(GLFWwindow* win, double xpos, double ypos) {
    for (auto& listener : Engine::get().m_mouseListeners)
        listener->CursorPosCallback(win, xpos, ypos);
}

void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (auto& listener : Engine::get().m_keyboardListeners)
        listener->KeyCallback(window, key, scancode, action, mods);
}

void Engine::RegisterToWindowResizeEvent(WindowResizeListener* listener) {
    m_resizeListeners.insert(listener);
}

void Engine::UnregisterToWindowResizeEvent(WindowResizeListener* listener) {
    m_resizeListeners.erase(listener);
}

void Engine::RegisterToMouseEvent(MouseListener* listener) {
    m_mouseListeners.insert(listener);
}

void Engine::UnregisterToMouseEvent(MouseListener* listener) {
    m_mouseListeners.erase(listener);
}

void Engine::RegisterToKeyboardEvent(KeyboardListener * listener) {
    m_keyboardListeners.insert(listener);
}

void Engine::UnregisterToKeyboardEvent(KeyboardListener* listener) {
    m_keyboardListeners.erase(listener);
}

Engine::~Engine() {
    glfwTerminate();
}