#include <monkey/activities/walk.h>
#include <gfx/engine.h>
#include <gfx/components/renderer.h>
#include <gfx/activities/animate.h>
#include <gfx/activities/move.h>
#include <gfx/math/shortestpath.h>
#include <glm/glm.hpp>
#include <gfx/math/closest.h>
#include <iostream>
#include <monkey/components/walkarea.h>
#include <monkey/activities/turn.h>
#include <gfx/activities/setstate.h>

void Walk::SetComplete() {

    Activity::SetComplete();
    // success if it managed ot get to the final point
    auto actor = Ref::GetFromId<Entity>(m_actorId);
    glm::vec2 currentPos(actor->GetPosition());
    m_success =(glm::length(m_p - currentPos) < 0.01);
}


void Walk::Start() {

    // if the walk has a tag, then get the id
    if (!m_tag.empty()) {
        m_actorId = Engine::get().getIdFromTag(m_tag);
    }
    // use the walk-area associated with the character

    //auto walkArea = Engine::get().GetRef<WalkArea>("walkarea");

    //std::cout << "Calling walk for " << m_actorId << " to " << m_p.x << ", " << m_p.y << "\n";
    auto actor = Ref::GetFromId<Entity>(m_actorId);

    // see if you have an associated walk-area
    auto walkArea = actor->GetParent()->GetComponent<WalkArea>();
    if (walkArea == nullptr) {
        std::cerr << ("The character is unable to walk as it's not associated to a walk area!\n");
        m_success = false;
        SetComplete();
        return;
    }

    m_shape = walkArea->GetShape();
    auto blockedLines = walkArea->GetActiveWalls();

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
        //int count = 0;
        //glm::vec2 currentPoint = points.front();
        std::string anim2;
        // set status to walk
        auto setStateAction = std::make_shared<SetState>("walk");
        setStateAction->SetId(m_actorId);
        Push(setStateAction);
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
            char dir;
            //std::string anim2;
            if (std::fabs(delta.x) > std::fabs(delta.y)) {
                dir = delta.x > 0 ? 'e' : 'w';
            } else {
                dir = delta.y > 0 ? 'n' : 's';
            }

            Push(std::make_shared<Turn>(m_actorId, dir));
            Push(std::make_shared<MoveTo>(m_actorId, currentPos + length * glm::normalize(delta), 20.0f, false, false));
            //if (i == points.size() - 1 || tMin < 1.0)
            currentPos = points[i];
            if (tMin < 1.0)
            {
                // I hit a wall!
                break;
            }
            //script->AddActivity(p);
        }
        auto setIdle = std::make_shared<SetState>("idle");
        setIdle->SetId(m_actorId);
        Push(setIdle);

        //Push(std::make_shared<SetState>(m_actorId, "idle"));

//        if (!anim2.empty())
  //          Push(std::make_shared<Animate>(actor, anim2, flipX));
    }
}
