#include "walk.h"
#include <monkey/engine.h>
#include <monkey/components/renderer.h>
#include <monkey/monkey.h>
#include <monkey/activities/animate.h>
#include <monkey/activities/move.h>
#include <monkey/math/shortestpath.h>
#include <glm/glm.hpp>
#include <monkey/math/closest.h>
#include <iostream>
#include "../components/walkarea.h"
#include "turn.h"
#include <monkey/activities/setstate.h>
#include "../components/character.h"

void Walk::SetComplete() {

    Activity::SetComplete();
    // success if it managed ot get to the final point	
    auto actor = Monkey::get().Get<Entity>(m_actorId);
    glm::vec2 currentPos(actor->GetPosition());
    m_success =(glm::length(m_p - currentPos) < 0.01);
}


void Walk::Start() {

    // if the walk has a tag, then get the id
    if (!m_tag.empty()) {
        m_actorId = Monkey::get().Get<Ref>(m_tag)->GetId();
    }
    // use the walk-area associated with the character

    //auto walkArea = Engine::get().GetRef<WalkArea>("walkarea");

    //std::cout << "Calling walk for " << m_actorId << " to " << m_p.x << ", " << m_p.y << "\n";
    auto actor = Monkey::get().Get<Entity>(m_actorId);
    float speed = actor->GetComponent<StateCharacter>()->GetSpeed();

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

    glm::vec3 currentPos(actor->GetPosition());
    //std::cout << "current position is " << currentPos.x << ", " << currentPos.y << "\n";
    // if current position is not in shape
    if (!m_shape->isPointInside(currentPos)) {

        auto p = ClosestPointOnEdge::Find(*(m_shape), currentPos);
        actor->SetPosition(p.P);
        currentPos = glm::vec3(p.P, 0.0f);

    }
    //std::cout << "current position is " << currentPos.x << ", " << currentPos.y << "\n";
    //std::cout << "target point is " << m_p.x << ", " << m_p.y << "\n";

    // if target point is not in shape
    if (!m_shape->isPointInside(glm::vec3(m_p, 0.0f))) {
        auto pos = ClosestPointOnEdge::Find(*(m_shape), m_p);
        m_p = pos.P + pos.normal*0.01f;
    }

    //std::cout << "target point is " << m_p.x << ", " << m_p.y << "\n";

    glm::vec2 pos2d(currentPos);
    glm::vec2 delta = m_p - pos2d;

    if (delta != glm::vec2(0.0f))
    {
        //std::cerr << "finding sp " << m_p.x << " " << m_p.y << "\n";
        std::vector<glm::vec2> points = ShortestPath::Find(*m_shape, currentPos, m_p);
        std::cerr << "ok\n";
        //int count = 0;
        //glm::vec2 currentPoint = points.front();
        std::string anim2;
        // set status to walk
        auto setStateAction = std::make_shared<SetState>("walk");
        setStateAction->SetId(m_actorId);
        Push(setStateAction);
        for (size_t i = 1; i < points.size(); ++i) {
            delta = points[i] - pos2d;
            float length = glm::length(delta);
            if (delta == glm::vec2(0.0f))
                continue;

            // see if this intersects one of the walls.
            // If it does, this is the last movement and it will end here
            float tMin = 1.0;
            for (auto& b : blockedLines) {
                float t = LineSegmentIntersection(pos2d, points[i], b.A, b.B);
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
            Push(std::make_shared<MoveToScaled>(m_actorId, pos2d + length * glm::normalize(delta), speed, false, false));
            //if (i == points.size() - 1 || tMin < 1.0)
            pos2d = points[i];
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
