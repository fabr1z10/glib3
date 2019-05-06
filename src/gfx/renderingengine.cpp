//
//  renderingengine.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#include <gfx/renderingengine.h>
#include <gfx/components/renderer.h>
#include <gfx/engine.h>
#include <gfx/math/geom.h>
#include <iostream>
#include <gfx/renderingiterator.h>

extern GLFWwindow* window;

//void RenderingStack::push(Entity* entity) {
//    // if the entity has a camera, we need to activate
//    Camera* cam = entity->GetCamera();
//    if (cam != nullptr) {
//        cam->SetProjectionMatrix();
//
//        // set the viewport
//        glm::vec4 vp = cam->GetViewPort();
//        glm::vec4 viewport;
//        if (m_viewportStack.empty()) {
//            viewport = vp;
//        } else {
//            glm::vec4 currentViewport = m_viewportStack.top();
//            float xMin = currentViewport.x + vp.x;
//            float yMin = currentViewport.y + vp.y;
//            float xMax = xMin + vp[2];
//            float yMax = yMin + vp[3];
//            xMin = Clamp(xMin, currentViewport.x, currentViewport.x + currentViewport[2]);
//            xMax = Clamp(xMax, currentViewport.x, currentViewport.x + currentViewport[2]);
//            yMin = Clamp(yMin, currentViewport.y, currentViewport.y + currentViewport[3]);
//            yMax = Clamp(yMax, currentViewport.y, currentViewport.y + currentViewport[3]);
//            // clamp to current viewport!
//            currentViewport = glm::vec4(xMin, yMin, xMax - xMin, yMax - yMin);
//        }
//        Engine::get().SetViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
//        m_cameras.push(cam);
//        m_viewportStack.push(viewport);
//    }
//    m_stack.push(entity);
//}
//
//bool RenderingStack::empty() const {
//    return m_stack.empty();
//}
//
//void RenderingStack::pop() {
//    // if the top entity has a camera,
//    // we need to reset the previous viewport
//    // and the previous projection matrix!
//    if (m_stack.top()->GetCamera() != nullptr) {
//        m_viewportStack.pop();
//        m_cameras.pop();
//
//        if (!m_cameras.empty()) {
//            glm::vec4 vp = m_viewportStack.top();
//            Engine::get().SetViewport(vp[0], vp[1], vp[2], vp[3]);
//            m_cameras.top()->SetProjectionMatrix();
//        }
//    }
//
//
//    m_stack.pop();
//
//
//};
//
//Entity* RenderingStack::top() {
//    return m_stack.top();
//}

void RenderingEngine::Start() {

    // trigger a resize

    // Engine::get().RegisterToWindowResizeEvent(this);
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


    Entity* root = Engine::get().GetScene();
    //std::cout << root->ToString() << "\n";
    for (auto& shader : m_shaders) {
        ShaderType stype = shader->GetShaderId();
        Shader::SetCurrentShader(shader.get());

        // loop through all nodes
        RenderingIterator iterator(root);
        for (; !iterator.end();) {
            // get the renderer component

            auto cam = iterator.GetCamera();
            if (cam == nullptr) {
                ++iterator;
                continue;
            }
            Entity& e = *iterator;
            //std::cout << "Examining " << e.GetTag() << "\n";
            if (!e.isActive()) {
                iterator.advanceSkippingChildren();
                continue;

            }
            Renderer* renderer = e.GetComponent<Renderer>();

            if (renderer != nullptr && renderer->isActive() && renderer->GetShaderType() == stype) {
                glm::mat4 wt = iterator->GetWorldTransform() * renderer->GetTransform();
                // check for frustrum culling ...
                drawCount++;
                        
                // compute model view matrix

                glm::mat4 mvm = cam->m_viewMatrix * wt;
                GLuint mvLoc = shader->GetUniformLocation(MODELVIEW);
                glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);
                renderer->Draw(shader.get());
            }
            ++iterator;

        }

    }
}

void RenderingEngine::AddShader (std::unique_ptr<Shader> s) {
//    Shader* shader = Engine::get().GetShader(id);
//    if (shader == nullptr)
//        GLIB_FAIL("Shader " << id << " is not available.");
    m_shaders.push_back(std::move(s));

}

void RenderingEngine::AddCamera(std::unique_ptr<Camera> cam) {

    if (Engine::get().isRunning()) {
        int widthPixel, heightPixel;
        glfwGetFramebufferSize(window, &widthPixel, &heightPixel);
        cam->Resize(widthPixel, heightPixel);
        // get the root entity for each camera
        std::string root = cam->GetRoot();
        auto rootNode = Ref::Get<Entity>(root).get();
        m_roots.insert(std::make_pair(cam.get(), rootNode));
    }
    m_cameras[cam->GetId()] = std::move(cam);

}

void RenderingEngine::RemoveCamera(int id) {
    m_cameras.erase(id);
}

void RenderingEngine::AddLight (Light* light) {
    m_lights.insert(light);
}

void RenderingEngine::RemoveLight(Light* light ) {
    m_lights.erase(light);
}