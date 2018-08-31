#include "gfx/collisionengine.h"
#include "graph/shape.h"
#include "gfx/entity.h"

void CollisionEngine::Add(Collider* c) {
    // this is called when a new collider starts. It registers with the engine
    // get the shape bounding box, transform it, map it
    Location loc = GetLocation(c);
    PushCollider(c, loc);
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
        if (loc != it->second) {
            // if it's still in the same region nbothing to do
            PopCollider(c);
            PushCollider(c, loc);
        }
    }

}

void CollisionEngine::PopCollider(Collider* c) {
    auto it = m_colliderLocations.find(c);
    if (it != m_colliderLocations.end()) {
        Location loc = it->second;
        for (int i = loc.x0; i <= loc.x1; ++i) {
            for (int j = loc.y0; i <= loc.y1; ++i) {
                auto& cell = m_cells[std::make_pair(i,j)];
                cell.colliders.erase(c);
                cell.dirty = true;
            }
        }

    }
}


void CollisionEngine::PushCollider(Collider* c, Location loc) {
    for (int i = loc.x0; i <= loc.x1; ++i) {
        for (int j = loc.y0; i <= loc.y1; ++i) {
            auto& cell = m_cells[std::make_pair(i,j)];
            cell.colliders.insert(c);
            cell.dirty = true;
        }
    }
    m_colliderLocations[c] = loc;
}

Location CollisionEngine::GetLocation(Collider* c) {
    auto& worldTransform = c->GetObject()->GetWorldTransform();
    auto aabb = c->GetShape()->getBounds();
    aabb.Transform(worldTransform);
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
    for (auto& cell : m_cells) {
        // skip cells that have less than 2 colliders
        if (!cell.second.dirty)
            continue;
        if (cell.second.colliders.size() < 2)
        {
            cell.second.dirty = false;
            continue;
        }

        for (auto& iter = cell.second.colliders.begin(), j = --cell.second.colliders.end(); iter != j; ++iter) {
            Collider* c1 = *iter;
            if (!c1->Enabled())
                continue;

            auto iter2 = iter;
            for (++iter2; iter2 != cell.second.colliders.end(); ++iter2) {
                Collider * c2 = *iter2;
                if (!c2->Enabled())
                    continue;
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
                Shape* s1 = c1->GetShape();
                Shape* s2 = c2->GetShape();
                glm::mat4& t1 = c1->GetObject()->GetWorldTransform();
                glm::mat4& t2 = c2->GetObject()->GetWorldTransform();
                s1->getBounds().Transform(t1);
                s2->getBounds().Transform(t2);

                s1->getBounds()
                // try first to do an aabb
                if (!s1->GetBoundingBox().Intersects(s2->GetBoundingBox()))
                    continue;

                // bounding boxes intersect, so let's make a propert collision test
                CollisionReport report = Intersection::Run(s1, s2);

                // check if these colliders were colliding in the previous frame
                auto np = make_pair(c1, c2);
                auto itercp = m_previouslyCollidingPairs.find(np);
                bool collidingBefore = (itercp != m_previouslyCollidingPairs.end());

                if (report.collide) {
                    // if the shapes are colldiing and they were not colliding before,
                    // a new collision response is generated
                    if (!collidingBefore) {
                        auto handler = factory.Create(c1->GetObject(), c2->GetObject(), report);
                        handler->Start();
                        m_previouslyCollidingPairs[np] = std::move(handler);
                    }
                    else {
                        itercp->second->UpdateReport(c1->GetObject(), report);
                        itercp->second->m_confirmed = true;
                    }
                }
                else {
                    if (collidingBefore) {
                        itercp->second->End();
                        m_previouslyCollidingPairs.erase(np);
                    }
                }
            }
        }
    }
    // remove pairs that were previously colliding but not now
    for (auto& iter = m_previouslyCollidingPairs.begin(); iter != m_previouslyCollidingPairs.end();) {
        if (!iter->second->m_confirmed) {
            iter->second->End();
            m_previouslyCollidingPairs.erase(iter++);
        }
        else {
            iter->second->Continue();
            iter++;
        }
    }
}