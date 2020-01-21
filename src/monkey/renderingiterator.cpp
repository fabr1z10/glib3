#include <monkey/renderingiterator.h>
#include <monkey/engine.h>
#include <monkey/math/geom.h>

void RenderingIterator::onPop(Entity* e) {
    if (e->GetCamera() != nullptr && !m_stack.empty()) {
        m_cameraStack.top().entity = m_stack.top();
    }
}

void RenderingIterator::onNext() {
    // if the top of the stack has a cmera
    if (!m_stack.empty()) {
        Entity* e = m_stack.top();
        while (!m_cameraStack.empty() && m_cameraStack.top().entity == e) {
            m_cameraStack.pop();
        }
        auto cam = e->GetCamera();
        if (cam != nullptr) {
            m_cameraStack.push({nullptr, cam});
            cam->SetProjectionMatrix();
            auto vp = cam->GetScreenViewPort();
            Engine::get().SetViewport(vp[0], vp[1], vp[2], vp[3]);
        }
    }
}

void HotSpotIterator::onPop(Entity* e) {
    if (e->GetCamera() != nullptr && !m_stack.empty()) {
        m_cameraStack.top().entity = m_stack.top();
    }
}

void HotSpotIterator::onNext() {
    // if the top of the stack has a cmera
    if (!m_stack.empty()) {
        Entity* e = m_stack.top();
        while (!m_cameraStack.empty() && m_cameraStack.top().entity == e) {
            m_cameraStack.pop();
        }
        auto cam = e->GetCamera();
        if (cam != nullptr) {
            m_cameraStack.push({nullptr, cam});
        }
    }
}

void ResizeIterator::onPop(Entity* e) {
    if (e->GetCamera() != nullptr && !m_stack.empty()) {
        m_cameraStack.top().entity = m_stack.top();
    }
}

void ResizeIterator::onNext() {
    // if the top of the stack has a cmera
    if (!m_stack.empty()) {
        Entity* e = m_stack.top();
        while (!m_cameraStack.empty() && m_cameraStack.top().entity == e) {
            m_cameraStack.pop();
        }
        auto cam = e->GetCamera();
        if (cam != nullptr) {
            // when I push a new camera, I also set the viewport
            glm::vec4 currentViewport = m_cameraStack.empty() ? glm::vec4(0.0f, 0.0f, Engine::get().GetDeviceSize()) : m_cameraStack.top().deviceViewport;
            glm::vec4 vp = cam->GetViewPort();
            float xMin = currentViewport.x + vp.x;
            float yMin = currentViewport.y + vp.y;
            float xMax = xMin + vp[2];
            float yMax = yMin + vp[3];
            xMin = Clamp(xMin, currentViewport.x, currentViewport.x + currentViewport[2]);
            xMax = Clamp(xMax, currentViewport.x, currentViewport.x + currentViewport[2]);
            yMin = Clamp(yMin, currentViewport.y, currentViewport.y + currentViewport[3]);
            yMax = Clamp(yMax, currentViewport.y, currentViewport.y + currentViewport[3]);
            glm::vec4 deviceViewport (xMin, yMin, xMax - xMin, yMax - yMin);
            glm::vec4 screenViewport = deviceToScreenViewport(deviceViewport);
            m_cameraStack.push({nullptr, cam, deviceViewport, screenViewport });
            cam->SetScreenViewPort(screenViewport);
        }
    }
}

Camera* RenderingIterator::GetCamera() {
    if (m_cameraStack.empty())
        return nullptr;
    return m_cameraStack.top().camera;
}
Camera* HotSpotIterator::GetCamera() {
    if (m_cameraStack.empty())
        return nullptr;
    return m_cameraStack.top().camera;
}



glm::vec4 ResizeIterator::deviceToScreenViewport(glm::vec4 vp) {
    glm::vec4 viewport;
    glm::vec2 deviceSize = Engine::get().GetDeviceSize();
    viewport[3] = static_cast<GLsizei> (m_actualSize.y * (vp[3] / deviceSize.y));
    viewport[2] = static_cast<GLsizei> (m_actualSize.x * (vp[2] / deviceSize.x));
    viewport.x = (m_winSize.x - m_actualSize.x) / 2.0f + vp.x * (m_actualSize.x / deviceSize.x);
    viewport.y = (m_winSize.y - m_actualSize.y) / 2.0f + vp.y * (m_actualSize.y / deviceSize.y);
    return viewport;
}

//void RenderingIterator::HandleCamera() {
//    // check if top entity has camera
//    m_changeCamera = false;
//    if (m_iter.m_stack.empty())
//        return;
//    Entity& e = *m_iter;
//
//    while (!m_viewportStack.empty() && !e.IsDescendantOf(m_viewportStack.top().entity)) {
//        m_viewportStack.pop();
//        m_changeCamera = true;
//    }
//    Camera* c = e.GetCamera();
//    if (c != nullptr) {
//        CameraInfo info;
//        info.camera = c;
//        info.entity = &e;
//
//        // set the viewport
//        glm::vec4 vp = c->GetViewPort();
//        glm::vec4 viewport;
//        if (m_viewportStack.empty()) {
//            viewport = vp;
//        } else {
//            glm::vec4 currentViewport = m_viewportStack.top().viewport;
//            float xMin = currentViewport.x + vp.x;
//            float yMin = currentViewport.y + vp.y;
//            float xMax = xMin + vp[2];
//            float yMax = yMin + vp[3];
//            xMin = Clamp(xMin, currentViewport.x, currentViewport.x + currentViewport[2]);
//            xMax = Clamp(xMax, currentViewport.x, currentViewport.x + currentViewport[2]);
//            yMin = Clamp(yMin, currentViewport.y, currentViewport.y + currentViewport[3]);
//            yMax = Clamp(yMax, currentViewport.y, currentViewport.y + currentViewport[3]);
//            // clamp to current viewport!
//            viewport = glm::vec4(xMin, yMin, xMax - xMin, yMax - yMin);
//        }
//        info.viewport = viewport;
//        m_changeCamera = true;
//        m_viewportStack.push(info);
//    } else {
//        // if I have a camera, check if the current node is a descedent
//        // of the current camera's entity. If not, pop and repeat until
//        // you either find a descendant or empty the viewport stack
//
//        // if you popped some cameras, need to reset the current
//
//    }
//
//    if (m_setCameras && m_changeCamera && !m_viewportStack.empty()) {
//
//        CameraInfo& c = m_viewportStack.top();
//        c.camera->SetProjectionMatrix();
//        Engine::get().SetViewport(c.viewport[0], c.viewport[1], c.viewport[2], c.viewport[3]);
//    }
//}
//
