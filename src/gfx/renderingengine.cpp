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
    for (auto& c : m_cameras) {
        auto cam = c.second.get();
        cam->Resize(widthPixel, heightPixel);
        // get the root entity for each camera
        std::string root = cam->GetRoot();
        Entity* rootNode = Engine::get().GetRef<Entity>(root);
        m_roots.insert(std::make_pair(cam, rootNode));
    }

    // register to window resize
    Engine::get().RegisterToWindowResizeEvent(this);
}

void RenderingEngine::Notify(float w, float h)  {
    //std::cout << "Changed window size to " << w << ", " << h << std::endl;
    for (auto& cam : m_cameras)
        cam.second->Resize(w, h);
}

void RenderingEngine::Update(double)
{
    int drawCount {0};
    //auto root = Engine::get().GetScene();
    for (auto& shader : m_shaders) {
        ShaderType stype = shader->GetShaderId();
        shader->Start();
        for (auto& c : m_cameras) {
            auto cam = c.second.get();
            cam->SetCurrentCamera(shader);
            auto it = m_roots.find(cam);
            if (it == m_roots.end())
                GLIB_FAIL ("Cannot find root for cam : " << cam->GetRoot());
            Entity *root = it->second;

            // loop through all nodes
            for (auto iter = root->begin(); iter != root->end(); ++iter) {

                // get the renderer component
                Renderer* renderer = iter->GetComponent<Renderer>();

                if (renderer != nullptr && renderer->IsActive() && renderer->GetShaderType() == stype) {
                    glm::mat4 wt = iter->GetWorldTransform() * renderer->GetTransform();
                    // check for frustrum culling ...
                    drawCount++;
                        
                    // compute model view matrix
                    glm::mat4 mvm = cam->m_viewMatrix * wt * renderer->GetRenderingTransform();
                    GLuint mvLoc = shader->GetUniformLocation(MODELVIEW);
                    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);
                    renderer->Draw(shader);
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

void RenderingEngine::AddCamera(std::unique_ptr<Camera> cam) {

    if (Engine::get().isRunning()) {
        int widthPixel, heightPixel;
        glfwGetFramebufferSize(window, &widthPixel, &heightPixel);
        cam->Resize(widthPixel, heightPixel);
        // get the root entity for each camera
        std::string root = cam->GetRoot();
        Entity* rootNode = Engine::get().GetRef<Entity>(root);
        m_roots.insert(std::make_pair(cam.get(), rootNode));
    }
    m_cameras[cam->GetId()] = std::move(cam);

}

void RenderingEngine::RemoveCamera(int id) {
    m_cameras.erase(id);
}