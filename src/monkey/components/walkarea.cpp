#include <monkey/components/walkarea.h>
#include <GLFW/glfw3.h>
#include <gfx/scheduler.h>
#include <monkey/activities/walk.h>
#include <gfx/engine.h>
#include <iostream>
#include <gfx/math/closest.h>
#include <gfx/math/shortestpath.h>

WalkArea::WalkArea(const WalkArea& orig) : HotSpot(orig), m_playerId(orig.m_playerId),
m_walls(orig.m_walls) {
    
}

std::shared_ptr<Component> WalkArea::clone() const {
    return std::make_shared<WalkArea>(WalkArea(*this));
}

void WalkArea::onAdd(Entity * e) {
    assignScaleAndDepth(e);
    e->onMove.Register(this, [&] (Entity* e) { assignScaleAndDepth(e);});

}


void WalkArea::assignScaleAndDepth (Entity* e) {
    e->setOnMoveEnabled(false);
    glm::vec2 pos = e->GetPosition();
    if (m_depthFunc != nullptr) {
        float z = m_depthFunc->operator()(pos.x, pos.y);
        e->SetZ(z);
        std::cout << "z is " << e->GetPosition().z << "\n";
    }

    if (m_scaleFunc != nullptr) {
        float scale = m_scaleFunc->operator()(pos.x, pos.y);
        e->SetScale(scale);
    }
    e->setOnMoveEnabled(true);
}

void WalkArea::Start() {
    HotSpot::Start();
    m_scheduler = Engine::get().GetRunner<Scheduler>();
    if (m_scheduler == nullptr) {
        GLIB_FAIL ("Walk area component needs a scheduler runner!");
    }
    m_player = Ref::Get<Entity>(m_playerId).get();
    m_id = m_player->GetId();
    // assign depth and scale to all children and register to their move event
    if (m_depthFunc != nullptr || m_scaleFunc != nullptr) {
        for (const auto &c : m_entity->GetChildren()) {
            assignScaleAndDepth(c.second.get());
            c.second->onMove.Register(this, [&] (Entity* e) { assignScaleAndDepth(e);});
        }
    }
    m_entity->onAdd.Register(this, [&] (Entity* e) { onAdd(e); });
    m_entity->onRemove.Register(this, [&] (Entity* e) {
        e->onMove.Unregister(this);
    });
}


void WalkArea::onClick(glm::vec2 worldCoords, int button, int action, int mods) {

    // here I need to answer this question:
    // is the character on the same walkarea? (in this case, just a walk)
    if (action == GLFW_PRESS) {
        if (m_player->GetParent() != this->m_entity) {
            std::cout << "Clicking on a different walkarea...";
            if (m_func != nullptr) {

                m_func->execute(m_player->GetParent()->GetTag(), worldCoords.x, worldCoords.y);
                return;
            }

            // see if I have a handler for (from: this, to: that, pos: worldcoords)
        }
        auto script = std::make_shared<Script>();
        script->AddActivity(1, std::unique_ptr<Walk>(new Walk(m_id, worldCoords)));
        script->AddEdge(0, 1);
        m_scheduler->AddScript("_walk", script);
    }
}

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

