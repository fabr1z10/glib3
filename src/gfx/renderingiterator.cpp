#include <gfx/renderingiterator.h>
#include <gfx/engine.h>
#include <graph/geom.h>

Camera* RenderingIterator::GetCamera() {
    if (m_viewportStack.empty())
        return nullptr;
    return m_viewportStack.top().camera;
}


void RenderingIterator::HandleCamera() {
    // check if top entity has camera
    m_changeCamera = false;
    if (m_iter.m_stack.empty())
        return;
    Entity& e = *m_iter;

    while (!m_viewportStack.empty() && !e.IsDescendantOf(m_viewportStack.top().entity)) {
        m_viewportStack.pop();
        m_changeCamera = true;
    }
    Camera* c = e.GetCamera();
    if (c != nullptr) {
        CameraInfo info;
        info.camera = c;
        info.entity = &e;

        // set the viewport
        glm::vec4 vp = c->GetViewPort();
        glm::vec4 viewport;
        if (m_viewportStack.empty()) {
            viewport = vp;
        } else {
            glm::vec4 currentViewport = m_viewportStack.top().viewport;
            float xMin = currentViewport.x + vp.x;
            float yMin = currentViewport.y + vp.y;
            float xMax = xMin + vp[2];
            float yMax = yMin + vp[3];
            xMin = Clamp(xMin, currentViewport.x, currentViewport.x + currentViewport[2]);
            xMax = Clamp(xMax, currentViewport.x, currentViewport.x + currentViewport[2]);
            yMin = Clamp(yMin, currentViewport.y, currentViewport.y + currentViewport[3]);
            yMax = Clamp(yMax, currentViewport.y, currentViewport.y + currentViewport[3]);
            // clamp to current viewport!
            currentViewport = glm::vec4(xMin, yMin, xMax - xMin, yMax - yMin);
        }
        info.viewport = viewport;
        m_changeCamera = true;
        m_viewportStack.push(info);
    } else {
        // if I have a camera, check if the current node is a descedent
        // of the current camera's entity. If not, pop and repeat until
        // you either find a descendant or empty the viewport stack

        // if you popped some cameras, need to reset the current

    }

    if (m_setCameras && m_changeCamera && !m_viewportStack.empty()) {

        CameraInfo& c = m_viewportStack.top();
        c.camera->SetProjectionMatrix();
        Engine::get().SetViewport(c.viewport[0], c.viewport[1], c.viewport[2], c.viewport[3]);
    }
}

