#include <monkey/hotspot.h>
#include <gfx/engine.h>
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
void HotSpotManager::Start() {
    for (auto& g : m_groups)
        g.second->InitCamera();

}
void HotSpotManager::AddGroup (int id, const std::string& camId) {

    m_groups[id] = std::unique_ptr<HotSpotGroup>(new HotSpotGroup(camId));
}

void HotSpotManager::Update(double dt) {
    

}


void HotSpotManager::CursorPosCallback(GLFWwindow*, double x, double y) {
    //std::cout << x << ", " << y << std::endl;
    for (auto& g : m_groups)
        g.second->Run(x, y);

}

void HotSpotGroup::InitCamera() {
    m_cam = Engine::get().GetRef<OrthographicCamera>(m_camId);
    m_cam->OnMove.Register(this, [this] (Camera*) { CameraMove(); });
}

void HotSpotGroup::Click(double x, double y) {
    if (m_active && m_currentlyActiveHotSpot != nullptr) {
        // convert mouse to world
        glm::vec2 wc = m_cam->GetWorldCoordinates(glm::vec2(x, y));
        m_currentlyActiveHotSpot->onClick(wc);
    }

}


void HotSpotGroup::CameraMove() {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    Run (x, y);
}

void HotSpotGroup::Run(double x, double y) {
    // see if current group is active (i.e. mouse position is in the group's cam viewport)
    bool isActive = m_cam->IsInViewport(x, y);

    if (isActive) {

        // check all the inner hotspots
        // convert mouse coords into world coordinates
        glm::vec2 worldCoords = m_cam->GetWorldCoordinates(glm::vec2(x, y));
        //std::cout << "world coords + " << worldCoords.x << ", " << worldCoords.y << std::endl;

        std::map<int, HotSpot*> candidateHotspots;
        for (auto& h : m_hotspots) {
            if (h->IsActive() && h->isMouseInside(worldCoords)) {
                candidateHotspots.insert(std::make_pair(-h->GetPriority(), h));
            }
        }
        
        if (candidateHotspots.empty()) {
            //std::cout << "no cand hotspot" << std::endl;
            if (m_currentlyActiveHotSpot != nullptr)
            {
                m_currentlyActiveHotSpot->SetFocus(false);
                m_currentlyActiveHotSpot = nullptr;
            }
        } else {
            auto hotspot = (candidateHotspots.begin()->second);
            //std::cout << "priority = " << candidateHotspots.begin()->first << std::endl;
            if (m_currentlyActiveHotSpot != nullptr && m_currentlyActiveHotSpot != hotspot)
                m_currentlyActiveHotSpot->SetFocus(false);
            hotspot->SetFocus(true);
            m_currentlyActiveHotSpot = hotspot;
        }

    } else {
        if (m_active && m_currentlyActiveHotSpot != nullptr) {
            m_currentlyActiveHotSpot->SetFocus(false);
            m_currentlyActiveHotSpot = nullptr;
        }
    }


    m_active = isActive;
}


void HotSpotManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
       double x, y ;
       glfwGetCursorPos(window, &x, &y);
       for (auto& g : m_groups) {
           g.second->Click(x, y);
       }
    }

}

void HotSpotManager::Register (HotSpot* hotspot) {
    m_groups[hotspot->GetGroup()]->Insert(hotspot);
}

void HotSpotManager::Unregister (HotSpot* hotspot) {
    m_groups[hotspot->GetGroup()]->Erase(hotspot);
}

void HotSpot::Start() {

    auto hs = (Engine::get().GetRef<HotSpotManager>("_hotspotmanager"));
    hs->Register(this);

}

HotSpot::~HotSpot() {
    try {
        auto hs = (Engine::get().GetRef<HotSpotManager>("_hotspotmanager"));
        hs->Unregister(this);
    } catch (Error& er) {

    }
}
