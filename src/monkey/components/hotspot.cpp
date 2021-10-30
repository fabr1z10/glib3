#include <monkey/components/hotspot.h>
#include <monkey/engine.h>
#include <monkey/components/renderer.h>
#include <monkey/meshfactory.h>
#include <monkey/iterator.h>
#include <monkey/assets/model.h>
#include <iostream>
#include <set>

extern GLFWwindow* window;

namespace py = pybind11;

HotSpot::HotSpot(const ITab& table) : m_shape(nullptr) {
    m_priority = table.get<int>("priority", 0);
    auto factory = Engine::get().GetSceneFactory();

    if (table.has("shape")) {
        auto shape_table = table["shape"];
        m_shape = factory->make2<IShape>(*shape_table);
    }
    m_focus = false;
}

HotSpot::HotSpot(const HotSpot& orig) :
Component(orig), m_shape(orig.m_shape), m_focus(orig.m_focus), m_priority(orig.m_priority) {
    
}

void HotSpotManager::Start() {

    // a hotspot manager requires a CAMERA!
    //m_entity->GetCamera();
    m_defaultCamera = m_entity->GetCamera(); //Monkey::get().Get<Camera>("maincam");
    if (m_defaultCamera == nullptr) {
        GLIB_FAIL("A hotspot manager needs to be attached to an entity with a camera!");
    }
}

bool HotSpot::isMouseInside(glm::vec2 pos) {
    glm::mat4 wt = glm::inverse(m_entity->GetWorldTransform());
    glm::vec3 lpos (wt * glm::vec4(pos.x, pos.y, 0.0f, 1.0f));
    //glm::vec2 lpos (m_entity->GetPosition());
    return m_shape->isPointInside(lpos);

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

HotSpotManager::HotSpotManager() : Component(), MouseListener(), m_currentlyActiveHotSpot{nullptr} {
    m_pixelRatio = Engine::get().GetPixelRatio();
}



HotSpotManager::HotSpotManager(const ITab& table) : Component(table) {
    m_currentlyActiveHotSpot = nullptr;
    m_pixelRatio = Engine::get().GetPixelRatio();

    // this is the function that gets called
    // if no hotspot is active when left mouse button is clicked,
    if (table.has("lmbclick")) {
        auto f = table.get<py::function>("lmbclick");
        setLmbClickCallback([f] (float x, float y) { f(x, y); });
        //setLmbClickCallback([f] (float x, float y) { f.execute(x, y);});
    }

    if (table.has("rmbclick")) {
        auto f = table.get<py::function>("rmbclick");
        setRmbClickCallback([f] (float x, float y) { f(x, y); });
        //setLmbClickCallback([f] (float x, float y) { f.execute(x, y);});
    }

}

HotSpotManager::~HotSpotManager() {
    std::cerr << "wind down the hs manager\n";
}
//bool HotSpotManager::IsInViewport(float xScreen, float yScreen, glm::vec4 activeViewport) {
//    xScreen *= m_pixelRatio;
//    yScreen *= m_pixelRatio;
//    if (xScreen < activeViewport.x || xScreen > activeViewport.x + activeViewport[2])
//        return false;
//    float winHeight = Engine::get().GetWindowSize().y;
//    float yFlipped = winHeight - yScreen;
//    if (yFlipped < activeViewport.y || yFlipped > activeViewport.y + activeViewport[3])
//        return false;
//    return true;
//}

void HotSpotManager::ScrollCallback(GLFWwindow*, double x, double y) {
    if (m_currentlyActiveHotSpot != nullptr && m_currentlyActiveHotSpot->GetObject()->isActive()) {
        m_currentlyActiveHotSpot->onScroll(x, y);
    }
}

// if I remove the hotspot currently active I get sigsegv!
void HotSpotManager::CursorPosCallback(GLFWwindow*, double x, double y) {

    // mouse has moved! let's find the current focussed hotspot
    //if (!m_active)
    //    return;
    bool isInViewport = m_defaultCamera->IsInViewport(x, y);
    if (!isInViewport) {
        if (m_currentlyActiveHotSpot != nullptr) {
            m_currentlyActiveHotSpot->onLeave();
            m_currentlyActiveHotSpot = nullptr;
        }
        return;
    }
    // loop through all hot-spots children of this entity
    //auto f
    HotSpot* newActiveHotSpot = nullptr;

    iterateDepth(m_entity, [&] (Entity * entity) {
        auto* hotspot = entity->GetComponent<HotSpot>();
        if (hotspot != nullptr &&
            (newActiveHotSpot == nullptr || (newActiveHotSpot->GetPriority() < hotspot->GetPriority()))) {
            // we need to convert screen coordinates to world coordinates
            // first observation we make is that the bottom left screen point given
            // by viewport.x and viewport.y, corresponds to the world point (cam.x - cam.width, cam.y - cam.height)
            glm::vec2 worldCoords = m_defaultCamera->GetWorldCoordinates(glm::vec2(x, y));
            if (hotspot->isMouseInside(worldCoords)) {
                newActiveHotSpot = hotspot;
                m_worldCoordinates = worldCoords;
            }
        }
    });

//    HotSpotIterator iterator(m_entity);
//
//
//    //bool isInViewport {false};
//    //OrthographicCamera* currentCam {nullptr};
//    //glm::vec4 viewport;
//    while (!iterator.end()) {
//        bool isInViewport = m_defaultCamera->IsInViewport(x, y);
//        if (isInViewport) {
//
//            //std::cout << iterator->GetPosition().x <<"\n";
//            HotSpot* hotspot = iterator->GetComponent<HotSpot>();
//            // only check if I don't have an active hotspot or if it has lower priority
//            if (hotspot != nullptr) {
//                std::cerr << "QUI\n";
//            }
//            if (hotspot != nullptr &&
//                    (newActiveHotSpot == nullptr || (newActiveHotSpot->GetPriority() < hotspot->GetPriority()))) {
//                // we need to convert screen coordinates to world coordinates
//                // first observation we make is that the bottom left screen point given
//                // by viewport.x and viewport.y, corresponds to the world point (cam.x - cam.width, cam.y - cam.height)
//                glm::vec2 worldCoords = m_defaultCamera->GetWorldCoordinates(glm::vec2(x, y));
//                if (hotspot->isMouseInside(worldCoords)) {
//                    newActiveHotSpot = hotspot;
//                    m_worldCoordinates = worldCoords;
//                }
//            }
//            ++iterator;
//        } else {
//            ++iterator;
//        }
//    }

    if (newActiveHotSpot != m_currentlyActiveHotSpot) {
        if (m_currentlyActiveHotSpot != nullptr) {
            //std::cout << "leaving\n";
            m_currentlyActiveHotSpot->onLeave();
        }
        m_currentlyActiveHotSpot = newActiveHotSpot;
        if (newActiveHotSpot != nullptr) {
            // notify me when you die!
            //std::cout << "entering\n";
            m_currentlyActiveHotSpot->onDestroy.Register(this, [&] (HotSpot* hs) { NotifyHotSpotDestructor(hs); });
            m_currentlyActiveHotSpot->onEnter();
        }

    } else {
        // the active hotspot is still the same, but the mouse has moved
        if (m_currentlyActiveHotSpot != nullptr)
        m_currentlyActiveHotSpot->onMove(m_worldCoordinates);
    }

}

//std::string HotSpotManager::toString() {
//    std::stringstream stream;
//    stream << "[HotSpotManager](tag = " << m_tag << ")";
//    return stream.str();
//}

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
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS && m_rmbClick) m_rmbClick(m_worldCoordinates.x, m_worldCoordinates.y);
        return;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (m_currentlyActiveHotSpot != nullptr && m_currentlyActiveHotSpot->GetObject()->isActive()) {
            std::cerr << "acco\n";
            m_currentlyActiveHotSpot->onClick(m_worldCoordinates, button, action, mods);
        } else {
            // convert mouse to world coordinates
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            if (m_defaultCamera->IsInViewport(xpos, ypos)) {
                glm::vec2 wp = m_defaultCamera->GetWorldCoordinates(glm::vec2(xpos, ypos));
                if (m_lmbClick) m_lmbClick(wp.x, wp.y);
            }
        }
    }

}

void HotSpotManager::KeyCallback(GLFWwindow *, int key, int scancode, int action, int mods) {
    // if a hotspot is focused, send the event
    KeyEvent k {key, action, mods};
    bool handled = false;
    if (m_currentlyActiveHotSpot != nullptr) {
        handled = m_currentlyActiveHotSpot->onKeyEvent(k);
    }
    if (!handled) {
        auto it = m_callbacks.find(k);
        if (it != m_callbacks.end())
            it->second();
    }

}


void HotSpot::SetParent(Entity * entity) {
    Component::SetParent(entity);
    if (m_shape != nullptr) {
        auto ptr =getDebugMesh();
        m_entity->AddChild(ptr);
    }
}

std::shared_ptr<Entity> HotSpot::getDebugMesh() {

    auto ce = std::make_shared<Entity>();

//    auto debugMesh = MeshFactory::CreateMesh(*(m_shape.get()), 5.0f);
//    auto model = std::make_shared<BasicModel>(debugMesh);
//    auto cer = std::make_shared<BasicRenderer>(model);
//
//    ce->AddComponent(cer);
//    ce->SetName("_debugmesh");
//
//    //m_entity->AddChild(ce);
    return ce;

}

void HotSpot::Start() {

    if (m_shape == nullptr) {
        // try to get shape from gfx component
        //auto renderer = m_entity->GetComponent<Renderer>();
        auto bounds = m_entity->GetComponent<Renderer>()->GetBounds2D();
        glm::vec2 extents = bounds.GetSize();
        SetShape(std::make_shared<Rect>(extents.x, extents.y, bounds.min));

        // if debug mode
        auto mesh = this->getDebugMesh();
        mesh->SetZ(2.0f);
        m_entity->AddChild(mesh);
    }

    if (m_shape != nullptr) {
        auto c = std::make_shared<Entity>();
        MeshFactory m;
        auto model = m.createWireframe(m_shape.get(), glm::vec4(1.0f));
        auto renderer = std::make_shared<Renderer>(model);
        c->AddComponent(renderer);
        c->SetZ(2.0f);
        m_entity->AddChild(c);
    }
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
