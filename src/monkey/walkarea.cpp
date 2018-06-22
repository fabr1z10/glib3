#include <monkey/walkarea.h>
#include <GLFW/glfw3.h>
#include <gfx/scheduler.h>
#include <monkey/walk.h>
#include <gfx/engine.h>
#include <iostream>
#include <graph/closest.h>
#include <graph/shortestpath.h>

void WalkArea::Start() {
    HotSpot::Start();

}

void WalkArea::onClick(glm::vec2 worldCoords) {
    std::cout << "CLICK ON WALKAREA\n";
    // find the target position. If I click inside the area, then that's my point, otherwise
    // I need to find the closest point in the edge of the polygon.
    //bool inside = m_shape->isPointInside(worldCoords);
    //std::cout << "Click at (" << worldCoords.x << ", "<< worldCoords.y  <<"), inside = " << inside<<std::endl;
    //if (!inside) {
    //    worldCoords = ClosestPointOnEdge::Find(*(m_shape.get()), worldCoords);
    //    std::cout << "closest point at (" << worldCoords.x << ", "<< worldCoords.y  <<")" << std::endl;
    //}

    // Now find the shortest path from player current position to the target pos.


    auto scheduler = Engine::get().GetRef<Scheduler>("_scheduler");
    //auto player = Engine::get().GetRef<Entity>("player");
    auto script = std::make_shared<Script>(0);
    script->AddActivity(std::unique_ptr<Walk>(new Walk(0, m_playerId, worldCoords)));
    scheduler->AddScript("_walk", script);

}

float WalkArea::GetDepth (float x, float y) {
    if (m_depthFunc == nullptr)
        GLIB_FAIL("Depth function not set for this walkarea");
    return m_depthFunc->operator()(x, y);
}

float WalkArea::GetScale (float x, float y) {
    if (m_scaleFunc == nullptr)
        GLIB_FAIL("Depth function not set for this walkarea");
    return m_scaleFunc->operator()(x, y);
}

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

