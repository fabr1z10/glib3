//#include <monkey/activities/walksci.h>
//#include <gfx/engine.h>
//#include <gfx/components/renderer.h>
//#include <gfx/activities/animate.h>
//#include <gfx/activities/move.h>
//#include <gfx/math/shortestpath.h>
//#include <glm/glm.hpp>
//#include <gfx/math/closest.h>
//#include <iostream>
//#include <monkey/components/walkarea.h>
//#include <monkey/activities/turn.h>
//#include <gfx/activities/setstate.h>
//#include <monkey/components/charactercomponent.h>
//#include <gfx/states/walk25.h>
//#include <gfx/activities/flip.h>
//
//void WalkSci::SetComplete() {
//
//    Activity::SetComplete();
//    // success if it managed ot get to the final point
//    auto actor = Ref::Get<Entity>(m_actorId);
//    glm::vec2 currentPos(actor->GetPosition());
//    m_success =(glm::length(m_p - currentPos) < 0.01);
//}
//
//
//void WalkSci::Start() {
//
//    // if the walk has a tag, then get the id
//    if (!m_tag.empty()) {
//        m_actorId = Ref::GetId(m_tag);
//    }
//
//    // use the walk-area associated with the character
//    auto actor = Ref::Get<Entity>(m_actorId);
//
//    // read the speed from walk state.
//    // ASSUMPTION: in order to walk, we need to have a state called <walk>
//    auto walkState = dynamic_cast<Walk25*>(actor->GetComponent<StateMachine>()->GetState("walk"));
//    bool fliph= walkState->flipHorizontally();
//    bool fourWay = walkState->isFourWay();
//    float speed = walkState->GetSpeed();
//
//    // see if you have an associated walk-area
//    auto walkArea = actor->GetParent()->GetComponent<WalkArea>();
//    if (walkArea == nullptr) {
//        std::cerr << ("The character is unable to walk as it's not associated to a walk area!\n");
//        m_success = false;
//        SetComplete();
//        return;
//    }
//
//    m_shape = walkArea->GetShape();
//    auto blockedLines = walkArea->GetActiveWalls();
//
//    glm::vec3 currentPos(actor->GetPosition());
//
//    // if current position is not in shape
//    if (!m_shape->isPointInside(currentPos)) {
//        auto p = ClosestPointOnEdge::Find(*(m_shape), currentPos);
//        actor->SetPosition(p);
//        currentPos = glm::vec3(p, 0.0f);
//
//    }
//
//    // if target point is not in shape
//    if (!m_shape->isPointInside(glm::vec3(m_p, 0.0f))) {
//        m_p = ClosestPointOnEdge::Find(*(m_shape), m_p);
//    }
//
//
//    glm::vec2 pos2d(currentPos);
//    glm::vec2 delta = m_p - pos2d;
//    char lastDirection;
//    if (delta != glm::vec2(0.0f))
//    {
//        std::vector<glm::vec2> points = ShortestPath::Find(*m_shape, currentPos, m_p);
//        //int count = 0;
//        //glm::vec2 currentPoint = points.front();
//        std::string anim2;
//        // set status to walk
//        auto setStateAction = std::make_shared<SetState>("walk");
//        setStateAction->SetId(m_actorId);
//        Push(setStateAction);
//        if (!fourWay) {
//            auto animAction = std::make_shared<Animate>("walk", true);
//            animAction->SetId(m_actorId);
//            Push(animAction);
//        }
//
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
//                dir = 'e';
//            } else {
//                dir = delta.y > 0 ? 'n' : 's';
//            }
//            lastDirection = dir;
//            // set the animation and direction
//            if (fliph) {
//
//                // update the sprite horizontal flip
//                auto flipAction = std::make_shared<Flip>(delta.x < 0 ? 2 :1);
//                flipAction->SetId(m_actorId);
//                Push(flipAction);
//            }
//            if (fourWay) {
//                std::stringstream stream ;
//                stream << "walk_" << dir;
//                auto animAction = std::make_shared<Animate>(stream.str(), true);
//                animAction->SetId(m_actorId);
//                Push(animAction);
//            }
//
//            //Push(std::make_shared<Turn>(m_actorId, dir));
//            Push(std::make_shared<MoveToScaled>(m_actorId, pos2d + length * glm::normalize(delta), speed, false, false));
//            //if (i == points.size() - 1 || tMin < 1.0)
//            pos2d = points[i];
//            if (tMin < 1.0)
//            {
//                // I hit a wall!
//                break;
//            }
//            //script->AddActivity(p);
//        }
//        //auto setIdle = std::make_shared<SetState>("idle");
//        //setIdle->SetId(m_actorId);
//        std::stringstream idleStream;
//        idleStream << "idle";
//        if (fourWay) {
//            idleStream << "_" << lastDirection;
//        }
//        auto animAction = std::make_shared<Animate>(idleStream.str(), true);
//        animAction->SetId(m_actorId);
//        Push(animAction);
//
//        //Push(std::make_shared<SetState>(m_actorId, "idle"));
//
////        if (!anim2.empty())
//        //          Push(std::make_shared<Animate>(actor, anim2, flipX));
//    }
//}
