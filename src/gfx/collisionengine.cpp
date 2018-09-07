#include "gfx/collisionengine.h"
#include "graph/shape.h"
#include "gfx/entity.h"
#include "graph/collisionreport.h"
#include <iostream>


CollisionEngine::CollisionEngine (float cellWidth, float cellHeight) : Ref(), m_width{cellWidth}, m_height{cellHeight}
{
    m_intersector = std::unique_ptr<Intersector>(new Intersector);
}


void CollisionEngine::Add(Collider* c) {
    // this is called when a new collider starts. It registers with the engine
    // get the shape bounding box, transform it, map it
    Location loc = GetLocation(c);
    PushCollider(c, loc);
    std::cout << "Adding collider " << c->GetShape()->toString() << " from (" << loc.x0 << ", " << loc.y0 << ") to (" << loc.x1 << ", " << loc.y1 << ")\n";
    // register to onmove

}

void CollisionEngine::Remove(Collider* c) {
    // called when a collider dies
    PopCollider(c);
}

void CollisionEngine::Move(Collider * c) {
    Location loc = GetLocation(c);
    auto it = m_colliderLocations.find(c);
    if (it != m_colliderLocations.end()) {
        if (it->second != loc) {
        std::cout << "Collider " << c->GetShape()->toString() << " moved to loc from (" << loc.x0 << ", " << loc.y0 << ") to (" << loc.x1 << ", " << loc.y1 << ")\n";
        if (loc != it->second) {
            // if it's still in the same region nbothing to do
            PopCollider(c);
            PushCollider(c, loc);
        }}
        else {
            // if the entity is still in the same cell range, I still need to make them dirty
            for (int i = loc.x0; i <= loc.x1; ++i) {
                for (int j = loc.y0; j <= loc.y1; ++j) {
                    auto& cell = m_cells[std::make_pair(i,j)];
                    cell.dirty = true;
                }
            }
        }
    } else {
        throw;
    }

}

void CollisionEngine::PopCollider(Collider* c) {
    auto it = m_colliderLocations.find(c);
    if (it != m_colliderLocations.end()) {
        Location loc = it->second;
        for (int i = loc.x0; i <= loc.x1; ++i) {
            for (int j = loc.y0; j <= loc.y1; ++j) {
                auto& cell = m_cells[std::make_pair(i,j)];
                cell.colliders.erase(c);
                cell.dirty = true;
            }
        }

    }
}


void CollisionEngine::PushCollider(Collider* c, Location loc) {
    for (int i = loc.x0; i <= loc.x1; ++i) {
        for (int j = loc.y0; j <= loc.y1; ++j) {
            auto& cell = m_cells[std::make_pair(i,j)];
            cell.colliders.insert(c);
            cell.dirty = true;
        }
    }
    m_colliderLocations[c] = loc;
}

Location CollisionEngine::GetLocation(Collider* c) {
    auto aabb = c->GetBounds();
    Location loc;
    loc.x0 = floor(aabb.min.x / m_width);
    float mx = aabb.max.x / m_width;
    int imx = floor(mx);
    if (imx == loc.x0 + 1 && (mx - imx == 0.0f)) imx--;
    loc.x1 = imx;
    loc.y0 = floor(aabb.min.y / m_height);
    float my = aabb.max.y / m_height;
    int imy = floor(my);
    if (imy == loc.y0 + 1 && (my - imy == 0.0f)) imy--;
    loc.y1 = imy;
    return loc;
}

void CollisionEngine::Update(double dt) {

    // loop throught all dirty cells and do a pair-wise collision detection for each collider within the cell.
    std::unordered_map<std::pair<Collider*, Collider*>, CollisionInfo> currentlyCollidingPairs;
    //std::cout << "Running collision engine update...\n";
    std::unordered_set<std::pair<int, int>> cellsExamined;
    //std::unordered_set<std::pair<Collider*, Collider*>> testedPairs;
    for (auto& cell : m_cells) {
        // skip cells that have less than 2 colliders
        if (!cell.second.dirty)
            continue;
        cellsExamined.insert(std::make_pair(cell.first.first, cell.first.second));
        if (cell.second.colliders.size() < 2)
        {
            cell.second.dirty = false;
            continue;
        }
        std::cout << "Examining cell " << cell.first.first << ", " << cell.first.second << "\n";
        for (auto iter = cell.second.colliders.begin(); iter != cell.second.colliders.end(); ++iter) {
            Collider* c1 = *iter;
            if (!c1->Enabled())
                continue;

            auto iter2 = iter;
            for (++iter2; iter2 != cell.second.colliders.end(); ++iter2) {
                Collider * c2 = *iter2;
                if (!c2->Enabled())
                    continue;
                // if no response is provided for these tags, then skip it
                if (!m_responseManager->HasCollision(c1, c2)) {
                    std::cout << "No response for tag (" << c1->GetTag() << ", " << c2->GetTag() << ")\n";
                    continue;
                }
//
//                // if we get here, collision is enabled on both nodes check now collision mask
//                int m1 = c1->GetCollisionFlag() & c2->GetCollisionMask();
//                int m2 = c2->GetCollisionFlag() & c1->GetCollisionMask();
//                bool collisionMaskTest = m1 || m2;
//                if (collisionMaskTest == 0)
//                    continue;
//
//                // do we have a collision response set up for this nodes?
//                auto factory = m_response->GetResponseFactory(c1, c2);
//                if (!factory.good())
//                    continue;

                // we have a collision response, so let's calculate collision
                auto b1 = c1->GetBounds();
                auto b2 = c2->GetBounds();
                
                // perform a aabb testing
                if (!b1.Intersects(b2)) {
                    std::cout << "aabb do not intersect\n";
                    continue;
                }
                std::cout << "aabb do intersect. Now do a proper testing\n";
                Shape* s1 = c1->GetShape();
                Shape* s2 = c2->GetShape();
                auto& t1 = c1->GetObject()->GetWorldTransform();
                auto& t2 = c2->GetObject()->GetWorldTransform();
                
                // bounding boxes intersect, so let's make a proper collision test
                CollisionReport report = m_intersector->Intersect(s1, t1, s2, t2);
                std::cout << "COllide = " << report.collide << "\n";
                if (report.collide) {
                    CollisionInfo ci;
                    ci.report = report;
                    ci.i = cell.first.first;
                    ci.j = cell.first.second;
                    currentlyCollidingPairs.insert(std::make_pair(std::make_pair(c1, c2), ci));
                }

                //testedPairs.insert(std::make_pair(c1, c2));
                //testedPairs.insert(std::make_pair(c2, c1));
                // check if these colliders were colliding in the previous frame
                //auto np = make_pair(c1, c2);
                //auto itercp = m_previouslyCollidingPairs.find(np);
                //bool collidingBefore = (itercp != m_previouslyCollidingPairs.end());

                //if (report.collide) {
                    // if the shapes are colldiing and they were not colliding before,
                    // a new collision response is generated
                //    if (!collidingBefore) {
                //        auto handler = factory.Create(c1->GetObject(), c2->GetObject(), report);
                //        handler->Start();
                //        m_previouslyCollidingPairs[np] = std::move(handler);
                //    }
                //    else {
                //        itercp->second->UpdateReport(c1->GetObject(), report);
                //        itercp->second->m_confirmed = true;
                //    }
                //}
                //else {
                //    if (collidingBefore) {
                //        itercp->second->End();
                //        m_previouslyCollidingPairs.erase(np);
                //    }
                //}
            }
            // set cell as not dirty
            cell.second.dirty = false;
        }
    }
    // remove pairs that were previously colliding but not now
    for (auto iter = m_previouslyCollidingPairs.begin(); iter != m_previouslyCollidingPairs.end();) {
        CollisionInfo& ci = iter->second;
        // If i have examined the cell AND they are not colliding anymore ...
        if (cellsExamined.count(std::make_pair(ci.i, ci.j))>0 && currentlyCollidingPairs.count(iter->first) == 0) {
            m_responseManager->onEnd (iter->first.first, iter->first.second, ci.report);
            m_previouslyCollidingPairs.erase(iter++);
        }
        else {
            iter++;
        }
    }

    for (auto& p : currentlyCollidingPairs) {
        auto it = m_previouslyCollidingPairs.find(p.first);
        if (it == m_previouslyCollidingPairs.end()) {
            m_responseManager->onStart (p.first.first, p.first.second, p.second.report);
            m_previouslyCollidingPairs.insert(std::make_pair(p.first, p.second));
        } else {
            m_responseManager->onStay(p.first.first, p.first.second, p.second.report);
            it->second = p.second;
        }
    }

    // add the new collision pairs
}

RayCastHit2D CollisionEngine::Raycast (glm::vec2 rayOrigin, glm::vec2 rayDir, float length, int mask) {
    return RayCastHit2D();
}