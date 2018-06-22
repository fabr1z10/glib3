#include <monkey/walk.h>
#include <gfx/engine.h>
#include <gfx/renderer.h>
#include <gfx/animate.h>
#include <gfx/move.h>
#include <graph/shortestpath.h>
#include <glm/glm.hpp>
#include <graph/closest.h>
#include <iostream>
#include <monkey/walkarea.h>


void Walk::Start() {
    auto walkArea = Engine::get().GetRef<WalkArea>("walkarea");
    m_shape = walkArea->GetShape();
    auto blockedLines = walkArea->GetActiveWalls();

    //std::cout << "Calling walk for " << m_actorId << " to " << m_p.x << ", " << m_p.y << "\n";
    auto actor = Engine::get().GetRef<Entity>(m_actorId);
    glm::vec2 currentPos(actor->GetPosition());

    // if current position is not in shape
    if (!m_shape->isPointInside(currentPos)) {
        glm::vec2 p = ClosestPointOnEdge::Find(*(m_shape), currentPos);
        actor->SetPosition(p);
        currentPos = p;

    }

    // if target point is not in shape
    if (!m_shape->isPointInside(m_p)) {
        m_p = ClosestPointOnEdge::Find(*(m_shape), m_p);
    }



    glm::vec2 delta = m_p - currentPos;
    if (delta != glm::vec2(0.0f))
    {
        std::vector<glm::vec2> points = ShortestPath::Find(*m_shape, currentPos, m_p);
        int count = 0;
        glm::vec2 currentPoint = points.front();
        std::string anim2;
        bool flipX{false};
        for (size_t i = 1; i < points.size(); ++i) {
            delta = points[i] - currentPos;
            float length = glm::length(delta);
            if (delta == glm::vec2(0.0f))
                continue;

            // see if this intersects one of the walls.
            // If it does, this is the last movement and it will end here
            float tMin = 1.0;
            for (auto& b : blockedLines) {
                float t = LineSegmentIntersection(currentPos, points[i], b.A, b.B);
                if (t > 0) {
                    tMin = std::min(tMin, t);
                }
            }
            // effective displacement
            if (tMin < 1.0) {
                length = tMin * length - 0.1f;
                length = std::max(0.0f, length);
            }
            if (length == 0.0f)
                break;
            std::string anim;
            //std::string anim2;
            if (std::fabs(delta.x) > std::fabs(delta.y)) {
                anim = "walk_right";
                anim2 = "idle_right";
            } else {
                if (delta.y > 0) {
                    anim = "walk_back";
                    anim2 = "idle_back";
                } else {
                    anim = "walk_front";
                    anim2 = "idle_front";
                }
            }
            flipX = (anim == "walk_right" && delta.x < 0);
            Push(std::make_shared<Animate>(count++, actor, anim, flipX));
            Push(std::make_shared<MoveTo>(count++, actor, currentPos + length * glm::normalize(delta), 200.0f));
            //if (i == points.size() - 1 || tMin < 1.0)
            currentPos = points[i];
            if (tMin < 1.0)
            {
                // I hit a wall!
                break;
            }
            //script->AddActivity(p);
        }
        if (!anim2.empty())
            Push(std::make_shared<Animate>(count++, actor, anim2, flipX));
    }
}
