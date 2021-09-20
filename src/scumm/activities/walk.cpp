#include "walk.h"
#include <monkey/engine.h>
#include <monkey/components/renderer.h>
#include <monkey/monkey.h>
#include <monkey/activities/animate.h>
#include <monkey/activities/move.h>
#include <monkey/math/algo/shortestpath.h>
#include <glm/glm.hpp>
#include <monkey/math/algo/closest.h>
#include <iostream>
#include "../components/walkarea.h"
#include "turn.h"
#include <monkey/activities/setstate.h>
#include "../components/character.h"
#include <monkey/components/animator.h>





Walk::Walk(const ITab& t) : Sequence(), m_pathFound(0) {
    m_p = t.get<glm::vec2>("pos");

    if (t.has("id")) {
        m_actorId = t.get<int>("id");
    } else {
        m_actorId = -1;
        m_tag = t.get<std::string>("tag");
    }



}
void Walk::SetComplete() {

    Activity::SetComplete();
    // success if it managed ot get to the final point	
    auto actor = Monkey::get().Get<Entity>(m_actorId);
    glm::vec2 currentPos(actor->GetPosition());
    // set to idle
    //auto animator = actor->GetComponent<IAnimator>();
    //auto currentAnim = animator->GetAnimation();
    //bool flipx = actor->GetFlipX();
    //char dir = currentAnim[currentAnim.size()-1];
    //if (dir == 'e' &&  flipx) dir = 'w';
    actor->GetComponent<CharacterController>()->turn(m_lastDirection);
    //m_success =(glm::length(m_p - currentPos) < 0.01);
    m_success = (m_pathFound == 0);
}


void Walk::Start() {

    // if the walk has a tag, then get the id
    if (!m_tag.empty()) {
        try {
            m_actorId = Monkey::get().Get<Ref>(m_tag)->GetId();
        } catch (Error& err) {
            std::cerr << err.what();
            SetComplete();
            return;
        }
    }
    // use the walk-area associated with the character
    auto actor = Monkey::get().Get<Entity>(m_actorId);
    auto walkArea = actor->GetParent()->GetComponent<WalkArea>();
    auto characterController = actor->GetComponent<CharacterController>();
    m_lastDirection = characterController->getDirection();
    auto speed = characterController->getSpeed();
//    //auto walkArea = Engine::get().GetRef<WalkArea>("walkarea");
//
//    //std::cout << "Calling walk for " << m_actorId << " to " << m_p.x << ", " << m_p.y << "\n";
//
//    float speed = actor->GetComponent<StateCharacter>()->GetSpeed();
//
//    // see if you have an associated walk-area
//    auto walkArea = actor->GetParent()->GetComponent<WalkArea>();
    if (walkArea == nullptr) {
        std::cerr << ("The character is unable to walk as it's not associated to a walk area!\n");
        m_success = false;
        SetComplete();
        return;
    }

    glm::vec2 currentPos(actor->GetPosition());
    auto dd = glm::length(currentPos - m_p);
    auto path = walkArea->findPath(currentPos, m_p, m_pathFound);

    if (path.empty()) {
        SetComplete();
        return;
    }
    // place actor in initial position
    actor->SetPosition(path.front());

    // for each line in polyline
    int flipH = 1;
    std::string anim;
    glm::vec2 lastMove;
    for (int i = 1; i < path.size(); ++i) {
        glm::vec2 move = path[i] - path[i-1];
		if (fabs(move.x) > fabs(move.y)) {
			m_lastDirection = (move.x >= 0) ? 'e' : 'w';
		} else {
			m_lastDirection = (move.y >= 0) ? 'n' : 's';
		}
        flipH = false;
        auto canim = characterController->getAnim("walk", move);
        auto setStateAction = std::make_shared<Animate>(canim.first, true, canim.second ? 2 : 1);
        setStateAction->SetId(m_actorId);
        Push(setStateAction);
        //auto moveAction = std::make_shared<MoveTo>(path[i], speed, false, false);
        auto moveAction = std::make_shared<MoveToScaled>(path[i], speed, false, false);
        moveAction->SetId(m_actorId);
        Push(moveAction);
        lastMove = move;
    }
    auto canim = characterController->getAnim("idle", lastMove);
    auto setStateAction = std::make_shared<Animate>(canim.first, true, canim.second ? 2 : 1);
    setStateAction->SetId(m_actorId);
    Push(setStateAction);


//        for (size_t i = 1; i < points.size(); ++i) {
//            delta = points[i] - pos2d;
//            float length = glm::length(delta);
//            if (delta == glm::vec2(0.0f))
//                continue;
//
//            // see if this intersects one of the walls.
//            // If it does, this is the last movement and it will end here
//            float tMin = 1.0;
//            for (auto& b : blockedLines) {
//                float t = LineSegmentIntersection(pos2d, points[i], b.A, b.B);
//                if (t > 0) {
//                    tMin = std::min(tMin, t);
//                }
//            }
//            // effective displacement
//            if (tMin < 1.0) {
//                length = tMin * length - 0.1f;
//                length = std::max(0.0f, length);
//            }
//            if (length == 0.0f)
//                break;
//            char dir;
//            //std::string anim2;
//            if (std::fabs(delta.x) > std::fabs(delta.y)) {
//                dir = delta.x > 0 ? 'e' : 'w';
//            } else {
//                dir = delta.y > 0 ? 'n' : 's';
//            }
//
//            Push(std::make_shared<Turn>(m_actorId, dir));
//            glm::vec2 P = pos2d + length * glm::normalize(delta);
//            Push(std::make_shared<MoveToScaled>(m_actorId, P, speed, false, false));
//            //std::cerr << "adding move to " << P.x << ", " << P.y << "\n";
//            //if (i == points.size() - 1 || tMin < 1.0)
//            pos2d = points[i];
//            if (tMin < 1.0)
//            {
//                // I hit a wall!
//                break;
//            }
//            //script->AddActivity(p);
//        }
//        auto setIdle = std::make_shared<SetState>("idle");
//        setIdle->SetId(m_actorId);
//        Push(setIdle);
//
//    std::cout << "current position is " << currentPos.x << ", " << currentPos.y << "\n";
//
//    // if current position is not in shape
//    glm::vec2 p0 = currentPos;
//    if (!shape->isPointInside(glm::vec3(currentPos, 0.0f))) {
//        auto& algo = ClosestPointOnEdge::get();
//        p0 = algo.find(currentPos, shape);
//        actor->SetPosition(p0);
//    }
//	// if target point is not in shape
//	if (!shape->isPointInside(glm::vec3(m_p, 0.0f))) {
//		auto& algo = ClosestPointOnEdge::get();
//		m_p = algo.find(m_p, shape);
//	}
//	std::cout << "target point is " << m_p.x << ", " << m_p.y << "\n";

            //auto p = ClosestPointOnEdge::Find(*(m_shape), currentPos);
////        glm::vec3 a (p.P + 0.5f* p.normal, 0.0f);
////        actor->SetPosition(a);
////        currentPos = a;
//
//    }
//    //std::cout << "current position is " << currentPos.x << ", " << currentPos.y << "\n";
//
//
//    //std::cout << "target point is " << m_p.x << ", " << m_p.y << "\n";
//
//    glm::vec2 pos2d(currentPos);
//    glm::vec2 delta = m_p - pos2d;
//
//    if (delta != glm::vec2(0.0f))
//    {
//        std::cerr << "delta " << delta.x << " " << delta.y << "\n";
//        std::cerr << "finding sp to " << m_p.x << " " << m_p.y << "\n";
//        std::cerr << "cpos " << currentPos.x << " " << currentPos.y << "\n";
//        std::vector<glm::vec2> points;
//        //std::vector<glm::vec2> points = ShortestPath::Find(*m_shape, currentPos, m_p);
//        //std::cerr << "ok\n";
//        //int count = 0;
//        //glm::vec2 currentPoint = points.front();
//        std::string anim2;
//        // set status to walk
//        auto setStateAction = std::make_shared<SetState>("walk");
//        setStateAction->SetId(m_actorId);
//        Push(setStateAction);
//        for (size_t i = 1; i < points.size(); ++i) {
//            delta = points[i] - pos2d;
//            float length = glm::length(delta);
//            if (delta == glm::vec2(0.0f))
//                continue;
//
//            // see if this intersects one of the walls.
//            // If it does, this is the last movement and it will end here
//            float tMin = 1.0;
//            for (auto& b : blockedLines) {
//                float t = LineSegmentIntersection(pos2d, points[i], b.A, b.B);
//                if (t > 0) {
//                    tMin = std::min(tMin, t);
//                }
//            }
//            // effective displacement
//            if (tMin < 1.0) {
//                length = tMin * length - 0.1f;
//                length = std::max(0.0f, length);
//            }
//            if (length == 0.0f)
//                break;
//            char dir;
//            //std::string anim2;
//            if (std::fabs(delta.x) > std::fabs(delta.y)) {
//                dir = delta.x > 0 ? 'e' : 'w';
//            } else {
//                dir = delta.y > 0 ? 'n' : 's';
//            }
//
//            Push(std::make_shared<Turn>(m_actorId, dir));
//            glm::vec2 P = pos2d + length * glm::normalize(delta);
//            Push(std::make_shared<MoveToScaled>(m_actorId, P, speed, false, false));
//            //std::cerr << "adding move to " << P.x << ", " << P.y << "\n";
//            //if (i == points.size() - 1 || tMin < 1.0)
//            pos2d = points[i];
//            if (tMin < 1.0)
//            {
//                // I hit a wall!
//                break;
//            }
//            //script->AddActivity(p);
//        }
//        auto setIdle = std::make_shared<SetState>("idle");
//        setIdle->SetId(m_actorId);
//        Push(setIdle);
//
//        //Push(std::make_shared<SetState>(m_actorId, "idle"));
//
////        if (!anim2.empty())
//  //          Push(std::make_shared<Animate>(actor, anim2, flipX));
//    } else {
//
//        SetComplete();
//    }
}
