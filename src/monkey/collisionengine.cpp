#include <monkey/collisionengine.h>
#include <iostream>
#include <monkey/math/raycast.h>
#include <monkey/luacollision.h>
#include <monkey/lua/luatable.h>

CollisionEngine::~CollisionEngine() {
    std::cerr << "Killing the ce\n";
    m_cells.clear();
    std::cerr << "qui\n";
    m_colliderLocations.clear();
    std::cerr << "qui2\n";
    m_intersector = nullptr;
    std::cerr << "qui3\n";
    // m_responseManager = nullptr;
    m_previouslyCollidingPairs.clear();
    std::cerr << "qui4\n";



}

CollisionEngine::CollisionEngine (float cellWidth, float cellHeight) :
        ICollisionEngine(), m_width{cellWidth}, m_height{cellHeight}, m_coll25d(false), m_eps(false)
{
    m_intersector = std::unique_ptr<Intersector>(new Intersector);
}

CollisionEngine::CollisionEngine(const LuaTable & table) : ICollisionEngine(table) {

    glm::vec2 collisionSize = table.Get<glm::vec2>("size");

    m_width = collisionSize.x;
    m_height = collisionSize.y;
    m_coll25d = table.Get<bool>("coll25", false);
    if (m_coll25d) {
        m_eps = table.Get<float>("eps", 0.01);
        Enable25DCollision(m_eps);
    }

    if (table.HasKey("response")) {

        auto resp = table.Get<luabridge::LuaRef>("response");
        std::unique_ptr<CollisionResponseManager> crm (new CollisionResponseManager);
        for (int i = 0; i < resp.length();++i) {
            luabridge::LuaRef a = resp[i+1];
            LuaTable at(a);
            std::vector<int> tags = at.GetVector<int>("tag");
            std::unique_ptr<LuaCollisionResponse> l(new LuaCollisionResponse);
            if (at.HasKey("onenter")) {
                auto onEnter = at.Get<luabridge::LuaRef>("onenter");
                l->SetOnEnter(onEnter);
            }
            if (at.HasKey("onleave")) {
                auto onLeave = at.Get<luabridge::LuaRef>("onleave");
                l->SetOnLeave(onLeave);
            }
            if (at.HasKey("onstay")) {
                auto onStay = at.Get<luabridge::LuaRef>("onstay");
                l->SetOnStay(onStay);
            }
            crm->AddCollisionResponse(tags[0], tags[1], std::move(l));

        }
        SetResponseManager(std::move(crm));
    }
}

void CollisionEngine::Enable25DCollision(float eps) {
    m_coll25d = true;
    m_eps = eps;
}

void CollisionEngine::Add(ICollider* c) {
    // this is called when a new collider starts. It registers with the engine
    // get the shape bounding box, transform it, map it
    auto aabb = c->GetBounds();
    if (!aabb.isVoid()) {
        Location loc = GetLocation(aabb);
        PushCollider(c, loc);
    }


}

void CollisionEngine::Remove(ICollider* c) {
    // called when a collider dies
    PopCollider(c, true);
}

void CollisionEngine::Clear() {
    m_cells.clear();
    m_colliderLocations.clear();
    m_previouslyCollidingPairs.clear();
}

void CollisionEngine::Move(ICollider * c) {

    auto it = m_colliderLocations.find(c);
    if (it != m_colliderLocations.end()) {
        auto aabb = c->GetBounds();
        Location loc = GetLocation(aabb);
        if (it->second != loc) {
            //std::cout << "Collider " << c->GetShape()->toString() << " moved to loc from (" << loc.x0 << ", " << loc.y0 << ") to (" << loc.x1 << ", " << loc.y1 << ")\n";
            if (loc != it->second) {
                // if it's still in the same region nbothing to do
                PopCollider(c, false);
                PushCollider(c, loc);
            }
        }
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
        Add(c);
    }

}

void CollisionEngine::PopCollider(ICollider* c, bool rmvPairs) {

    auto it = m_colliderLocations.find(c);
    //std::cerr << "CALLED POP COLLIDER! " << c->GetShape()->getBounds().GetSize().x << "\n";
    if (it != m_colliderLocations.end()) {
        Location loc = it->second;
        //std::cerr << "Collider at " << loc.x0 << ", " << loc.x1 << ", " << loc.y0 << ", " << loc.y1 << "\n";
        for (int i = loc.x0; i <= loc.x1; ++i) {
            for (int j = loc.y0; j <= loc.y1; ++j) {
                auto& cell = m_cells[std::make_pair(i,j)];
                cell.colliders.erase(c);
                cell.dirty = true;
                //std::cerr << "No. of colliders in (" << i << ", " << j << ") = " << cell.colliders.size() << "\n";
            }
        }

    }

    if (rmvPairs) {
        for (auto it = m_previouslyCollidingPairs.cbegin(); it != m_previouslyCollidingPairs.cend();) {
            if (it->first.first == c || it->first.second == c) {
                it = m_previouslyCollidingPairs.erase(it);
            } else {
                ++it;
            }
        }
    }
}


void CollisionEngine::PushCollider(ICollider* c, Location loc) {
    for (int i = loc.x0; i <= loc.x1; ++i) {
        for (int j = loc.y0; j <= loc.y1; ++j) {
            auto& cell = m_cells[std::make_pair(i,j)];
            cell.colliders.insert(c);
            cell.dirty = true;
        }
    }
    m_colliderLocations[c] = loc;
}

Location CollisionEngine::GetLocation(const Bounds& aabb) {
    //auto aabb = c->GetBounds();
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
    std::unordered_map<std::pair<ICollider*, ICollider*>, CollisionInfo> currentlyCollidingPairs;
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
        //std::cout << "Examining cell " << cell.first.first << ", " << cell.first.second << "\n";
        for (auto iter = cell.second.colliders.begin(); iter != cell.second.colliders.end(); ++iter) {
            ICollider* c1 = *iter;
            if (!c1->isActive())
                continue;
            float z1 = c1->GetObject()->GetPosition().z;
            auto iter2 = iter;
            for (++iter2; iter2 != cell.second.colliders.end(); ++iter2) {
                ICollider * c2 = *iter2;
                float z2 = c2->GetObject()->GetPosition().z;
                if (!c2->isActive())
                    continue;
                // check collision mask
                if ( ((c1->GetCollisionMask() & c2->GetCollisionFlag()) == 0) && ((c2->GetCollisionMask() & c1->GetCollisionFlag()) == 0)) {
                    // If at least one mask is hit, then we keep checking the collision.
                    // if both mask fail, then we skip to the next collider
                    continue;
                }

                // if no response is provided for these tags, then skip it
                if (m_responseManager == nullptr || !m_responseManager->HasCollision(c1, c2)) {
                    //std::cout << "No response for tag (" << c1->GetTag() << ", " << c2->GetTag() << ")\n";
                    continue;
                }
                // 2.5d collision check
                if (m_coll25d && fabs(z1-z2) > m_eps) {
                    continue;
                }


                // we have a collision response, so let's calculate collision
                auto b1 = c1->GetBounds();
                auto b2 = c2->GetBounds();
                
                // perform a aabb testing
                if (!b1.Intersects2D(b2)) {
                    //std::cout << "aabb do not intersect\n";
                    continue;
                }
                //std::cout << "aabb do intersect. Now do a proper testing\n";
                Shape* s1 = c1->GetShape();
                Shape* s2 = c2->GetShape();
                if (s1 == nullptr || s2 == nullptr) {
                    continue;
                }
                auto& t1 = c1->GetObject()->GetWorldTransform();
                auto& t2 = c2->GetObject()->GetWorldTransform();
                
                // bounding boxes intersect, so let's make a proper collision test
                CollisionReport report = m_intersector->Intersect(s1, t1, s2, t2);
                //std::cout << "COllide = " << report.collide << "\n";
                if (report.collide) {
                    CollisionInfo ci;
                    ci.report = report;
                    ci.i = cell.first.first;
                    ci.j = cell.first.second;
                    currentlyCollidingPairs.insert(std::make_pair(std::make_pair(c1, c2), ci));
                }


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

ShapeCastHit CollisionEngine::ShapeCast (std::shared_ptr<Shape> shape, const glm::mat4& transform, int mask) {
    ShapeCastHit result;
    auto aabb = shape->getBounds();
    aabb.Transform(transform);
    float z = transform[3][2];
    Location loc = GetLocation(aabb);
    for (int i = loc.x0; i <= loc.x1; ++i) {
        for (int j = loc.y0; j <= loc.y1; ++j) {
            auto cell = m_cells.find(std::make_pair(i, j));
            if (cell != m_cells.end()) {
                auto& colliders = cell->second.colliders;
                for (auto& c : colliders) {
                    if (!c->isActive()) {
                        continue;
                    }

                    int flag = c->GetCollisionFlag();
                    int m = flag & mask;
                    if (m == 0) {
                        continue;
                    }
                    auto b = c->GetBounds();
                    float zc = c->GetObject()->GetPosition().z;
                    // 2.5d collision check
                    if (m_coll25d && fabs(z-zc) > m_eps) {
                        continue;
                    }
                    // perform a aabb testing
                    if (!aabb.Intersects(b)) {
                        continue;
                    }
                    Shape* s = c->GetShape();
                    auto& t = c->GetObject()->GetWorldTransform();

                    // bounding boxes intersect, so let's make a proper collision test
                    CollisionReport report = m_intersector->Intersect(shape.get(), transform, s, t);
                    if (report.collide) {
                        result.report = report;
                        result.entity = c;
                        return result;
                    }
                }
            }
        }
    }
    return result;

}

RayCastHit CollisionEngine::Raycast (glm::vec3 rayOrigin, glm::vec3 rayDir, float length, int mask, bool use_z) {

    glm::vec3 P = rayOrigin;
    glm::vec3 P1 = P;
    float z = rayOrigin.z;
    // initialize current cell
    int i = static_cast<int>(P.x / m_width);
    int j = static_cast<int>(P.y / m_height);

    // distance to h0it the vertical lines:
    // ((i+\xi)*delta - P) / u_x, where

    int n = (rayDir.x > 0 ? 1 : 0);
    int m = (rayDir.y > 0 ? 1 : 0);
    // n = 0 <-> r_x = 0 <-> vertical line
    // m = 0 <-> r_y = 0 <-> horizontal line
    float l = 0.0f;
    bool endReached = false;

    RayCastHit out;
    out.length = length;

    while (!endReached && !out.collide) {
        // get the next point into this cell
        float t1 = (rayDir.x == 0.0f) ? std::numeric_limits<float>::infinity() : ((i+n)*m_width - P.x) / rayDir.x;
        float t2 = (rayDir.y == 0.0f) ? std::numeric_limits<float>::infinity() : ((j+m)*m_height - P.y) / rayDir.y;
        float tm = std::min(t1, t2);

        if (l + tm < length) {
            // need to add a tiny extra bit in case the colliding object is a line that lies exactly at the border
            // of two neighboring cell!
            P1 = P + (tm+0.01f) * rayDir;
        } else {
            P1 = P + length * rayDir;
            endReached = true;
        }

        // get the colliders at the current cell
        auto it = m_cells.find(std::make_pair(i, j));
        Line line (P, P1);
        auto lineBounds = line.getBounds();
        if (it != m_cells.end()) {
            for (auto& c : it->second.colliders) {
                if (!c->isActive())
                    continue;
                // aabb check
                int flag = c->GetCollisionFlag();
                int m = flag & mask;

                if (m != 0) {
                    float zc = c->GetObject()->GetPosition().z;
                    if (use_z && zc > -2 && m_coll25d && fabs(z-zc) > m_eps) {
                        continue;
                    }
                    auto shapeBounds = c->GetBounds();
                    if (lineBounds.Intersects2D(shapeBounds)) {
                        auto t = c->GetObject()->GetWorldTransform();
                        RayCast2D rc(rayOrigin, rayDir, length, t);
                        c->GetShape()->accept(rc);
                        auto report = rc.GetResult();
                        if (report.collide && (!out.collide || out.length > report.length)) {
                            out = report;
                            out.entity = c;// ->GetObject();
                            out.collide = true;
                            //return out;
                        }
                    }
                }
            }
        }
        P = P1;
        l += tm;
        if (t1 < t2) {
            i += (rayDir.x > 0 ? 1 : -1);
        } else {
            j += (rayDir.y > 0 ? 1 : -1);
        }

    }
//    if (out.collide) {
//        std::cout << "Collide! length = " << out.length << "\n";
//    }
    return out;

}

std::string CollisionEngine::toString() {
    std::stringstream stream;
    stream << "[CollisionEngine](tag = " << m_tag << ", size = (" << m_width << ", " << m_height << ")";
    return stream.str();
}


std::type_index CollisionEngine::GetType() {
    return std::type_index(typeid(ICollisionEngine));
}
