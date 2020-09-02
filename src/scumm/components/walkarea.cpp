#include "walkarea.h"
#include <GLFW/glfw3.h>
#include <monkey/scheduler.h>

#include <monkey/engine.h>
#include <iostream>
#include <monkey/math/closest.h>
#include <monkey/math/shortestpath.h>
#include <monkey/properties.h>

WalkArea::WalkArea(std::shared_ptr<Shape> shape, int priority) : ScriptHotSpot(shape, priority) {}

WalkArea::WalkArea(const WalkArea& orig) : ScriptHotSpot(orig),
m_walls(orig.m_walls) {
    
}



WalkArea::WalkArea(const ITable & t) : ScriptHotSpot(t) {
    auto factory = Engine::get().GetSceneFactory();
    
    if (t.hasKey("depth")) {
        auto dref = t.get<PyTable>("depth");
        auto depthFunc = factory->make2<Function2D>(dref);
        SetDepthFunction(depthFunc);
    }
    
    if (t.hasKey("scale")) {
        auto dref = t.get<PyTable>("scale");
        auto scaleFunc = factory->make2<Function2D>(dref);
        SetScalingFunction(scaleFunc);
    }
    
    if (t.hasKey("blocked_lines")) {
        t.foreach<PyDict>("blocked_lines", [&] (const PyDict& d) {
            auto A = d.get<glm::vec2>("A");
            auto B = d.get<glm::vec2>("B");
            auto active = d.get<bool>("active", true);
            AddBlockedLine(A, B, active);
        });
//        luabridge::LuaRef ref = t.Get<luabridge::LuaRef>("blockedlines");
//        for (int i = 0; i < ref.length(); ++i) {
//            luabridge::LuaRef bl = ref[i+1];
//            LuaTable t(bl);
//            glm::vec2 A = t.Get<glm::vec2>("A");
//            glm::vec2 B = t.Get<glm::vec2>("B");
//            bool active = t.Get<bool>("active");
//            AddBlockedLine(A, B, active);
//        }
     }
}


std::shared_ptr<Component> WalkArea::clone() const {
    return std::make_shared<WalkArea>(WalkArea(*this));
}

void WalkArea::onAdd(Entity * e) {
//    auto props = e->GetComponent<Properties>();
//    if (props != nullptr) {
//        luabridge::LuaRef scale = props->get("walkarea_scale");
//        if (!scale.isNil()) {
//            bool wsc = scale.cast<bool>();
//            if (!wsc) {
//                assignDepth(e);
//                e->onMove.Register(this, [&] (Entity*) { assignDepth(e); });
//                return;
//            }
//        }
//    }
    assignScaleAndDepth(e);
    e->onMove.Register(this, [&] (Entity* e) { assignScaleAndDepth(e);});

}

void WalkArea::assignDepth (Entity* e) {

    e->setOnMoveEnabled(false);
    glm::vec2 pos = e->GetPosition();
    if (m_depthFunc != nullptr) {
        float z = m_depthFunc->operator()(pos.x, pos.y);

        e->SetZ(z);
        //std::cout << "z is " << e->GetPosition().z << "\n";
    }
    e->setOnMoveEnabled(true);
}


void WalkArea::assignScaleAndDepth (Entity* e) {
    e->setOnMoveEnabled(false);
    glm::vec2 pos = e->GetPosition();
    if (m_depthFunc != nullptr) {
        float z = m_depthFunc->operator()(pos.x, pos.y);
        e->SetZ(z);
        //std::cout << "z is " << e->GetPosition().z << "\n";
    }

    if (m_scaleFunc != nullptr) {
        float scale = m_scaleFunc->operator()(pos.x, pos.y);
        e->SetScale(scale);
    }
    e->setOnMoveEnabled(true);
}

std::shared_ptr<Entity> WalkArea::getDebugMesh() {
    auto ptr = HotSpot::getDebugMesh();
//    auto props = std::make_shared<Properties>();
//    //return nullptr;
//    luabridge::LuaRef ciao = LuaWrapper::makeTable();
//    ciao["walkarea_scale"] = false;
//    props->addAdditionalProps(ciao);
//    ptr->AddComponent(props);
    return ptr;
}

void WalkArea::Start() {
    ScriptHotSpot::Start();

    if (m_depthFunc != nullptr || m_scaleFunc != nullptr) {
        for (const auto &c : m_entity->GetChildren()) {
            onAdd(c.second.get());
        }
    }
    m_entity->onAdd.Register(this, [&] (Entity* e) { onAdd(e); });
    m_entity->onRemove.Register(this, [&] (Entity* e) {
        e->onMove.Unregister(this);
    });

    // automatically add a collider component. WHY ???
    //auto coll = std::make_shared<SimpleCollider>(m_shape,1,2,1);
    //m_entity->AddComponent(coll);
    //coll->Start();

}


//void WalkArea::onClick(glm::vec2 worldCoords, int button, int action, int mods) {
//
//    // here I need to answer this question:
//    // is the character on the same walkarea? (in this case, just a walk)
//    if (action == GLFW_PRESS) {
//        if (m_player->GetParent() != this->m_entity) {
//            std::cout << "Clicking on a different walkarea...";
//            if (m_func != nullptr) {
//
//                m_func->execute(m_player->GetParent()->GetTag(), worldCoords.x, worldCoords.y);
//                return;
//            }
//
//            // see if I have a handler for (from: this, to: that, pos: worldcoords)
//        }
//        auto script = std::make_shared<Script>();
//        script->AddActivity(1, std::unique_ptr<Walk>(new Walk(m_id, worldCoords)));
//        script->AddEdge(0, 1);
//        m_scheduler->AddScript("_walk", script);
//    }
//}

//float WalkArea::GetDepth (float x, float y) {
//    if (m_depthFunc == nullptr)
//        GLIB_FAIL("Depth function not set for this walkarea");
//    return m_depthFunc->operator()(x, y);
//}
//
//float WalkArea::GetScale (float x, float y) {
//    if (m_scaleFunc == nullptr)
//        GLIB_FAIL("Depth function not set for this walkarea");
//    return m_scaleFunc->operator()(x, y);
//}

void WalkArea::AddBlockedLine(glm::vec2 A, glm::vec2 B, bool active) {
    m_walls.push_back( BlockedLine { LineSegment{A, B}, active });
}

void WalkArea::EnableBlockedLine(int i, bool value) {
    m_walls[i].active = value;

}

std::vector<LineSegment> WalkArea::GetActiveWalls() const {
    std::vector<LineSegment> segs;
    for (auto& m : m_walls) {
        if (m.active)
            segs.push_back(m.seg);
    }
    return segs;
}

