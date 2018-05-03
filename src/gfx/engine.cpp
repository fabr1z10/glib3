#include "gfx/engine.h"
#include "gfx/app.h"


void Engine::MainLoop() {

    if (!glfwWindowShouldClose(m_window)) {

        // load the scene

        // start the scene

        // run the scene
        while (!glfwWindowShouldClose(m_window)) {
            double currentTime = glfwGetTime();
            if (currentTime - m_timeLastUpdate >= m_frameTime) {
                m_timeLastUpdate = currentTime;
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glfwSwapBuffers(m_window);
                glfwPollEvents();
            }
        }
    }
}