#include "gfx/collisionengine.h"
#include "graph/shape.h"
#include "gfx/entity.h"

void CollisionEngine::Add(Collider* c) {
    // this is called when a new collider starts. It registers with the engine
    // get the shape bounding box, transform it, map it
    auto& worldTransform = c->GetObject()->GetWorldTransform();
}

Location CollisionEngine::GetLocation(Collider* c) {
    Bounds aabb = c->GetBoundingBox();// c->GetShape()->GetBoundingBox();
    Location loc;
    loc.i0 = floor(aabb.min.x / m_width);
    float mx = aabb.max.x / m_width;
    int imx = floor(mx);
    if (imx == loc.i0 + 1 && (mx - imx == 0.0f)) imx--;
    loc.i1 = imx;
    loc.j0 = floor(aabb.min.y / m_height);
    float my = aabb.max.y / m_height;
    int imy = floor(my);
    if (imy == loc.j0 + 1 && (my - imy == 0.0f)) imy--;
    loc.j1 = imy;
    return loc;
}

void CollisionEngine::Update(double dt) {
    // step 1.
    // loop through each collider.
    // if dirty, update its position in the grid.
    // if out of scope, remove it from the grid.
    // make dirty all cells impacted.
    for (auto iter = m_colliders.begin(); iter != m_colliders.end(); ) {
        if (g_alive.find(iter->first) == g_alive.end()) {
            Remove(iter->second);
            m_colliders.erase(iter++);
            continue;
        }
        if (iter->second.dirty) {
            Collider* c = iter->second.collider;
            Location loc = GetLocation(c->GetShape());
            if (loc == iter->second.loc) {
                // mark cells as dirty
                iter++;
                continue;
            }
            Remove(iter->second);
            Add(c);
        }
        ++iter;
    }

    // mark all previous colliding pairs as unconfirmed, so they get removed if no longer colliding
    for (auto& iter = m_previouslyCollidingPairs.begin(); iter != m_previouslyCollidingPairs.end(); ++iter) {
        iter->second->m_confirmed = false;
    }

    // step 2.
    // loop throught all dirty cells and do a pair-wise collision detection for each collider within the cell.
    for (auto& cell : m_cells) {
        // skip cells that have less than 2 colliders
        if (cell.second.colliders.size() < 2)
            continue;
        //if (cell.second.dirty) {
        //	continue;
        //}
        for (auto& iter = cell.second.colliders.begin(), j = --cell.second.colliders.end(); iter != j; ++iter) {
            Collider* c1 = *iter;
            if (!c1->Enabled())
                continue;

            auto iter2 = iter;
            for (++iter2; iter2 != cell.second.colliders.end(); ++iter2) {
                Collider * c2 = *iter2;
                if (!c2->Enabled())
                    continue;

                // if we get here, collision is enabled on both nodes check now collision mask
                int m1 = c1->GetCollisionFlag() & c2->GetCollisionMask();
                int m2 = c2->GetCollisionFlag() & c1->GetCollisionMask();
                bool collisionMaskTest = m1 || m2;
                if (collisionMaskTest == 0)
                    continue;

                // do we have a collision response set up for this nodes?
                auto factory = m_response->GetResponseFactory(c1, c2);
                if (!factory.good())
                    continue;

                // we have a collision response, so let's calculate collision
                Shape* s1 = c1->GetShape();
                Shape* s2 = c2->GetShape();

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