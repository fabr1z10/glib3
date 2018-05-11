//
//  renderingengine.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#include <gfx/renderingengine.h>
#include <gfx/renderer.h>
#include <gfx/engine.h>
#include <gfx/shader.h>
#include <gfx/error.h>
#include <iostream>

extern GLFWwindow* window;

void RenderingEngine::Start() {

    // trigger a resize for all cameras
    int widthPixel, heightPixel;
    glfwGetFramebufferSize(window, &widthPixel, &heightPixel);
    for (auto& cam : m_cameras)
        cam->Resize (widthPixel, heightPixel);

    // register to window resize
    Engine::get().RegisterToWindowResizeEvent(this);
}

RenderingEngine::~RenderingEngine() {
    Engine::get().UnregisterToWindowResizeEvent(this);
}

void RenderingEngine::Notify(float w, float h)  {
    //std::cout << "Changed window size to " << w << ", " << h << std::endl;
    for (auto& cam : m_cameras)
        cam->Resize(w, h);
}

void RenderingEngine::Update(double)
{
    int drawCount {0};
    auto root = Engine::get().GetScene();
    for (auto& shader : m_shaders) {
        ShaderType stype = shader->GetShaderId();
        shader->Start();
        for (auto& cam : m_cameras) {
            cam->SetCurrentCamera(shader);
            int camLayer = cam->GetLayer();
            // loop through all nodes
            for (auto iter = root->begin(); iter != root->end(); ++iter) {
                if ( (camLayer & iter->GetLayer()) > 0) {
                    // get the renderer component
                    Renderer* renderer = iter->GetComponent<Renderer>();
                    
                    if (renderer != nullptr && renderer->GetShaderType() == stype) {
                        glm::mat4 wt = iter->GetWorldTransform() * renderer->GetTransform();
                        // check for frustrum culling ...
                        drawCount++;
                        
                        // compute model view matrix
                        glm::mat4 mvm = cam->m_viewMatrix * wt;
                        GLuint mvLoc = shader->GetUniformLocation(MODELVIEW);
                        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);
                        renderer->Draw(shader);
                    }
                    
                }
            }
        }
        shader->Stop();
    }
}

void RenderingEngine::AddShader (ShaderType id) {
    Shader* shader = Engine::get().GetShader(id);
    if (shader == nullptr)
        GLIB_FAIL("Shader " << id << " is not available.");
    m_shaders.push_back(shader);

}