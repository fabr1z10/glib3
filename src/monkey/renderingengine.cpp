//
//  renderingengine.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#include <monkey/renderingengine.h>
#include <monkey/components/renderer.h>
#include <monkey/engine.h>
#include <monkey/math/geom.h>
#include <iostream>
#include <monkey/renderingiterator.h>

extern GLFWwindow* window;


RenderingEngine::RenderingEngine() : Component(), WindowResizeListener(), m_i(0) {}

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

void RenderingEngine::setupCamera(Camera* cam) {
	cam->SetProjectionMatrix();
	auto vp = cam->GetScreenViewPort();
	Engine::get().SetViewport(vp[0], vp[1], vp[2], vp[3]);
}


void RenderingEngine::Update(double)
{
    int drawCount {0};
    //auto root = Engine::get().GetScene();


    Entity* root = Engine::get().GetScene();
    //std::cout << root->ToString() << "\n";
    for (auto& shader : m_shaders) {
        ShaderType stype = shader->GetShaderId();
        //shader->initVertexAttributes();
        //GLuint mvLoc = shader->GetUniformLocation(MODELVIEW);
        // start the shader
        Shader::SetCurrentShader(shader.get());

        // loop through all nodes depth-first, maintaining the order of insertion
        std::list<Entity*> nodesToProcess;
        std::list<std::pair<int, Camera*>> cameras;
        nodesToProcess.push_back(root);
        Camera* currentCam = nullptr;
        while (!nodesToProcess.empty()) {
        	// get current node
        	auto node = nodesToProcess.front();
        	nodesToProcess.pop_front();
			if (node->isActive()) {
				// *** handle camera
				auto cam = node->GetCamera();
				if (!cameras.empty() && node->GetId() == cameras.front().first) {
					// pop the camera
					cameras.pop_front();
					// if current node does not have a camera, initialize the old camera, if any
					if (cam == nullptr && !cameras.empty()) {
						currentCam = cameras.front().second;
						setupCamera(currentCam);
					}
				}
				// check if current node has a camera, in this case push it, and initialize it
				if (cam != nullptr) {
					cameras.push_front(std::make_pair(nodesToProcess.empty() ? -1 : nodesToProcess.front()->GetId(), cam));
					currentCam = cameras.front().second;
					setupCamera(currentCam);
				}
				// *** end handle camera
				auto* renderer = node->GetComponent<Renderer>();
				if (currentCam != nullptr && renderer != nullptr && renderer->isActive() /*&& renderer->GetShaderType() == stype*/) {
					glm::mat4 wt = node->GetWorldTransform() * renderer->GetTransform();
					// check for frustrum culling ...
					drawCount++;
					// compute model view matrix
					//m_mvm = wt;
					glm::mat4 mvm = currentCam->m_viewMatrix * wt;
					//glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);
					shader->initMesh(wt, currentCam);
					renderer->init(shader.get());
					renderer->Draw(shader.get());
					renderer->post();
				}
				// add children, go reverse order
				const auto& children = node->GetChildren();
				for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
					for (auto iter2 = iter->second.rbegin(); iter2 != iter->second.rend(); ++iter2) {
						nodesToProcess.push_front(iter2->get());
					}
				}
			}
        }

        shader->Stop();

    }
}

void RenderingEngine::AddShader (std::unique_ptr<Shader> s) {
//    Shader* shader = Engine::get().GetShader(id);
//    if (shader == nullptr)
//        GLIB_FAIL("Shader " << id << " is not available.");
    m_shaders.push_back(std::move(s));

}
//
//void RenderingEngine::AddCamera(std::unique_ptr<Camera> cam) {
//
//    if (Engine::get().isRunning()) {
//        int widthPixel, heightPixel;
//        glfwGetFramebufferSize(window, &widthPixel, &heightPixel);
//        cam->Resize(widthPixel, heightPixel);
//        // get the root entity for each camera
//        std::string root = cam->GetRoot();
//        auto rootNode = Monkey::get().Get<Entity>(root);
//        m_roots.insert(std::make_pair(cam.get(), rootNode));
//    }
//    m_cameras[cam->GetId()] = std::move(cam);
//
//}
//
//void RenderingEngine::RemoveCamera(int id) {
//    m_cameras.erase(id);
//}

void RenderingEngine::AddLight (Light* light) {
    m_lights.insert(light);
}

void RenderingEngine::RemoveLight(Light* light ) {
    m_lights.erase(light);
}

//glm::mat4& RenderingEngine::getModelViewMatrix() {
//    return m_mvm;
//}

//Camera* RenderingEngine::getCurrentCamera() {
//    return m_currentCamera;
//}