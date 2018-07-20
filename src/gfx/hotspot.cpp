#include <gfx/hotspot.h>
#include <gfx/engine.h>
#include <gfx/renderer.h>
#include <gfx/meshfactory.h>
#include <gfx/renderingiterator.h>
#include <iostream>
#include <set>

extern GLFWwindow* window;

bool HotSpot::isMouseInside(glm::vec2 pos) {
    glm::vec2 lpos (m_entity->GetPosition());
    return m_shape->isPointInside(pos - lpos);

}


void HotSpot::SetFocus(bool focus) {
    if (focus != m_focus) {
        if (focus)
            onEnter();
        else
            onLeave();
        m_focus = focus;
    }


}

HotSpotManager::HotSpotManager() : Ref(), MouseListener(), m_active{true}, m_currentlyActiveHotSpot{nullptr} {
    m_pixelRatio = Engine::get().GetPixelRatio();
}

bool HotSpotManager::IsInViewport(float xScreen, float yScreen, glm::vec4 activeViewport) {
    xScreen *= m_pixelRatio;
    yScreen *= m_pixelRatio;
    if (xScreen < activeViewport.x || xScreen > activeViewport.x + activeViewport[2])
        return false;
    float winHeight = Engine::get().GetWindowSize().y;
    float yFlipped = winHeight - yScreen;
    if (yFlipped < activeViewport.y || yFlipped > activeViewport.y + activeViewport[3])
        return false;
    return true;
}

// if I remove the hotspot currently active I get sigsegv!
void HotSpotManager::CursorPosCallback(GLFWwindow*, double x, double y) {

    // mouse has moved! let's find the current focussed hotspot
    if (!m_active)
        return;
    Entity* root = Engine::get().GetScene();
    RenderingIterator iterator(root, false);

    bool isInViewport {false};
    OrthographicCamera* currentCam {nullptr};
    glm::vec4 viewport;
    HotSpot* newActiveHotSpot = nullptr;
    while (iterator != RenderingIterator()) {
        if (!iterator->IsActive() || !iterator->AreControlsEnabled())
        {
            iterator.advanceSkippingChildren();
            continue;
        }
        if (iterator.changedCamera() && iterator.hasActiveViewport()) {
            // if we have a new ORTHO camera
            auto orthoCam = dynamic_cast<OrthographicCamera*>(iterator.GetCamera());
            if (orthoCam != nullptr) {
                viewport = iterator.GetCurrentViewport();
                viewport = Engine::get().GetViewport(viewport.x, viewport.y, viewport[2], viewport[3]);
                // check if point is inside viewport
                isInViewport = IsInViewport(x, y, viewport);

                if (isInViewport) {
                    currentCam = orthoCam;
                    //std::cout << "in camera viewport = " << viewport.x << ", " << viewport.y << ", " << viewport[2] << ", " << viewport[3] << "\n";
                }

            } else {
                isInViewport = false;
            }
            // if it's not in this camera, there's no point
            // in visiting its children, so we skip all of them.
            if (!isInViewport) {
                iterator.advanceSkippingChildren();
                continue;
            }
        } else {
            if (!isInViewport) {
                ++iterator;
                continue;
            }
        }
        HotSpot* hotspot = iterator->GetComponent<HotSpot>();
        // only check if I don't have an active hotspot or if it has lower priority

        if (hotspot != nullptr &&
                (newActiveHotSpot == nullptr || (newActiveHotSpot->GetPriority() < hotspot->GetPriority()))) {

            // we need to convert screen coordinates to world coordinates
            // first observation we make is that the bottom left screen point given
            // by viewport.x and viewport.y, corresponds to the world point (cam.x - cam.width, cam.y - cam.height)
            glm::vec2 orthoSize = currentCam->GetSize();
            float x0 = -currentCam->m_viewMatrix[3][0] - orthoSize.x * 0.5f;
            float y0 = -currentCam->m_viewMatrix[3][1] - orthoSize.y * 0.5f;
            float winHeight = Engine::get().GetWindowSize().y;
            float ty = (winHeight/m_pixelRatio) - y;
            float xw = x0 + (x - viewport.x / m_pixelRatio) * (orthoSize.x / (viewport[2] / m_pixelRatio));
            float yw = y0 + (ty - viewport.y / m_pixelRatio) * (orthoSize.y / (viewport[3] / m_pixelRatio));
            //std::cout << xw << "," << yw << "\n";
            if (hotspot->isMouseInside(glm::vec2(xw, yw))) {
                //std::cout << "INSIDE!\n";
                newActiveHotSpot = hotspot;
                m_worldCoordinates = glm::vec2(xw, yw);
            }
        }
        ++iterator;
    }

    if (newActiveHotSpot != m_currentlyActiveHotSpot) {
        if (m_currentlyActiveHotSpot != nullptr) {
            //std::cout << "LEAVING\n";
            m_currentlyActiveHotSpot->onLeave();
        }
        m_currentlyActiveHotSpot = newActiveHotSpot;
        if (newActiveHotSpot != nullptr) {
            //std::cout << "ENTER\n";
            // notify me when you die!
            m_currentlyActiveHotSpot->onDestroy.Register(this, [&] (HotSpot* hs) { NotifyHotSpotDestructor(hs); });
            m_currentlyActiveHotSpot->onEnter();
        }

    }

}

//void HotSpotGroup::InitCamera() {
//    m_cam = Engine::get().GetRef<OrthographicCamera>(m_camId);
//    m_cam->OnMove.Register(this, [this] (Camera*) { CameraMove(); });
//}
//
//void HotSpotGroup::Click(double x, double y) {
//    if (m_active && m_currentlyActiveHotSpot != nullptr) {
//        // convert mouse to world
//        glm::vec2 wc = m_cam->GetWorldCoordinates(glm::vec2(x, y));
//        m_currentlyActiveHotSpot->onClick(wc);
//    }
//
//}
//
//
//void HotSpotGroup::CameraMove() {
//    double x, y;
//    glfwGetCursorPos(window, &x, &y);
//    Run (x, y);
//}
//
//void HotSpotGroup::Run(double x, double y) {
//    // see if current group is active (i.e. mouse position is in the group's cam viewport)
//    if (!m_enabled)
//    {
//        return;
//    }
//    bool isActive = m_cam->IsInViewport(x, y);
//
//    if (isActive) {
//
//        // check all the inner hotspots
//        // convert mouse coords into world coordinates
//        glm::vec2 worldCoords = m_cam->GetWorldCoordinates(glm::vec2(x, y));
//        std::cout << x << "," << y << ", world coords = " << worldCoords.x << ", " << worldCoords.y << std::endl;
//
//        std::map<int, HotSpot*> candidateHotspots;
//        for (auto& h : m_hotspots) {
//            if (h->IsActive() && h->isMouseInside(worldCoords)) {
//
//                candidateHotspots.insert(std::make_pair(-h->GetPriority(), h));
//            }
//        }
//        std::cout << candidateHotspots.size() << "\n";
//        if (candidateHotspots.empty()) {
//            //std::cout << "no cand hotspot" << std::endl;
//            if (m_currentlyActiveHotSpot != nullptr)
//            {
//                m_currentlyActiveHotSpot->SetFocus(false);
//                m_currentlyActiveHotSpot = nullptr;
//            }
//        } else {
//            auto hotspot = (candidateHotspots.begin()->second);
//            //std::cout << "priority = " << candidateHotspots.begin()->first << std::endl;
//            if (m_currentlyActiveHotSpot != nullptr && m_currentlyActiveHotSpot != hotspot)
//                m_currentlyActiveHotSpot->SetFocus(false);
//            hotspot->SetFocus(true);
//            m_currentlyActiveHotSpot = hotspot;
//        }
//
//    } else {
//        if (m_active && m_currentlyActiveHotSpot != nullptr) {
//            m_currentlyActiveHotSpot->SetFocus(false);
//            m_currentlyActiveHotSpot = nullptr;
//        }
//    }
//
//
//    m_active = isActive;
//}


void HotSpotManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (m_currentlyActiveHotSpot != nullptr && m_currentlyActiveHotSpot->GetObject()->IsActive()) {
            //uble x, y ;
            //fwGetCursorPos(window, &x, &y);
            m_currentlyActiveHotSpot->onClick(m_worldCoordinates);
        }


    }

}


void HotSpot::SetParent(Entity * entity) {
    Component::SetParent(entity);
    auto ce = std::make_shared<Entity>();
    auto cer = std::make_shared<Renderer>();
    auto debugMesh = MeshFactory::CreateMesh(*(m_shape.get()), 5.0f);
    cer->SetMesh(debugMesh);
    ce->AddComponent(cer);
    ce->SetTag("hotspotmesh");
    m_entity->AddChild(ce);
}

void HotSpot::Start() {

    //auto hs = (Engine::get().GetRef<HotSpotManager>("_hotspotmanager"));
    //hs->Register(this);
    // if DEBUG

}

HotSpot::~HotSpot() {
    onDestroy.Fire(this);
}

void HotSpotManager::NotifyHotSpotDestructor(HotSpot* hotspot) {
    if (hotspot == m_currentlyActiveHotSpot)
        m_currentlyActiveHotSpot = nullptr;
}
//void HotSpotManager::EnableGroup(int group) {
//    auto iter = m_groups.find(group);
//    if (iter == m_groups.end())
//        GLIB_FAIL("EnableGroup: unknown group " << group);
//    iter->second->SetEnabled(true);
//}
//void HotSpotManager::DisableGroup(int group) {
//    auto iter = m_groups.find(group);
//    if (iter == m_groups.end())
//        GLIB_FAIL("DisableGroup: unknown group " << group);
//    iter->second->SetEnabled(false);
//}
//