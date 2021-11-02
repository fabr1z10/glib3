#include <monkey/collisionengine.h>
#include <iostream>
#include <monkey/math/raycast2d.h>
#include <monkey/luacollision.h>
#include <monkey/math/raycast3d.h>

namespace py = pybind11;

SpatialHashingCollisionEngine::~SpatialHashingCollisionEngine() {
    std::cerr << "Killing the ce\n";
    m_cells.clear();
    m_colliderLocations.clear();
    m_intersector = nullptr;
    // m_responseManager = nullptr;
    m_previouslyCollidingPairs.clear();



}

SpatialHashingCollisionEngine::SpatialHashingCollisionEngine(const ITab & table) : ICollisionEngine(table) {

    m_size = table.get<glm::vec2>("size");

    // choose between 2d or 3d intersector
	m_intersector = std::make_unique<Intersector2D>();
	m_raycast = std::make_unique<RayCast2D>();
}

void SpatialHashingCollisionEngine::Add(ICollider* c) {
    // this is called when a new collider starts. It registers with the engine
    // get the shape bounding box, transform it, map it
    auto aabb = c->GetBounds();
    if (!aabb.isVoid()) {
        auto loc = getLocation(aabb);
        PushCollider(c, loc.first, loc.second);
    }


}

void SpatialHashingCollisionEngine::Remove(ICollider* c) {
    // called when a collider dies
    PopCollider(c, true);
}

void SpatialHashingCollisionEngine::Clear() {
    m_cells.clear();
    m_colliderLocations.clear();
    m_previouslyCollidingPairs.clear();
}

void SpatialHashingCollisionEngine::Move(ICollider * c) {

    auto it = m_colliderLocations.find(c);
    if (it != m_colliderLocations.end()) {
        auto aabb = c->GetBounds();
        // get the new location
        auto loc = getLocation(aabb);
        if (it->second != loc) {
            PopCollider(c, false);
            PushCollider(c, loc.first, loc.second);
        }
        else {
            // if the entity is still in the same cell range, I still need to make them dirty
            for (int i = loc.first.x; i <= loc.second.x; ++i) {
                for (int j = loc.first.y; j <= loc.second.y; ++j) {
                    m_cells[glm::ivec2(i, j)].dirty = true;
                }
            }
        }
    } else {
        Add(c);
    }

}

void SpatialHashingCollisionEngine::PopCollider(ICollider* c, bool rmvPairs) {

    auto it = m_colliderLocations.find(c);
    //std::cerr << "CALLED POP COLLIDER! " << c->GetShape()->getBounds().GetSize().x << "\n";
    if (it != m_colliderLocations.end()) {
        auto loc = it->second;
        for (int i = loc.first.x; i <= loc.second.x; ++i) {
            for (int j = loc.first.y; j <= loc.second.y; ++j) {
                auto &cell = m_cells[glm::ivec2(i, j)];
                cell.colliders.erase(c);
                cell.dirty = true;
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


void SpatialHashingCollisionEngine::PushCollider(ICollider* c, glm::ivec2 m, glm::ivec2 M) {
    for (int i = m.x; i <= M.x; ++i) {
        for (int j = m.y; j <= M.y; ++j) {
            auto &cell = m_cells[glm::ivec2(i, j)];
            cell.colliders.insert(c);
            cell.dirty = true;
        }
    }
    m_colliderLocations[c] = std::make_pair(m, M);
}

std::pair<glm::ivec2, glm::ivec2> SpatialHashingCollisionEngine::getLocation(const Bounds &b) {
    glm::ivec2 min(0);
    glm::ivec2 max(0);
    min.x = floor(b.min.x / m_size[0]);
    min.y = floor(b.min.y / m_size[1]);
    max.x = floor(b.max.x / m_size[0]);
    max.y = floor(b.max.y / m_size[1]);
    return std::make_pair(min, max);
}


// TODO remove
//Location CollisionEngine::GetLocation(const Bounds& aabb) {
//    //auto aabb = c->getBounds();
//    Location loc;
//    loc.x0 = floor(aabb.min.x / m_width);
//    float mx = aabb.max.x / m_width;
//    int imx = floor(mx);
//    if (imx == loc.x0 + 1 && (mx - imx == 0.0f)) imx--;
//    loc.x1 = imx;
//    loc.y0 = floor(aabb.min.y / m_height);
//    float my = aabb.max.y / m_height;
//    int imy = floor(my);
//    if (imy == loc.y0 + 1 && (my - imy == 0.0f)) imy--;
//    loc.y1 = imy;
//    return loc;
//}

void SpatialHashingCollisionEngine::Update(double dt) {

    // loop throught all dirty cells and do a pair-wise collision detection for each collider within the cell.
    std::unordered_map<std::pair<ICollider*, ICollider*>, CollisionInfo> currentlyCollidingPairs;
    //std::cout << "Running collision engine update...\n";
    std::unordered_set<glm::ivec2> cellsExamined;
    //std::unordered_set<std::pair<Collider*, Collider*>> testedPairs;
    for (auto& c : m_cells) {
        auto& cell = c.second;
        if (!cell.dirty) {
            continue;
        }
		cellsExamined.insert(c.first);
        // skip cells that have less than 2 colliders
        if (cell.colliders.size() < 2) {
            cell.dirty = false;
            continue;
        }
        //cellsExamined.insert(std::make_pair(cell.first.first, cell.first.second));
        //std::cout << "Examining cell " << cell.first.first << ", " << cell.first.second << "\n";
        for (auto iter = cell.colliders.begin(); iter != cell.colliders.end(); ++iter) {
            ICollider* c1 = *iter;
            if (!c1->isActive())
                continue;
            auto iter2 = iter;
            for (++iter2; iter2 != cell.colliders.end(); ++iter2) {
                ICollider * c2 = *iter2;
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
                    continue;
                }

                // we have a collision response, so let's calculate collision
                auto b1 = c1->GetBounds();
                auto b2 = c2->GetBounds();
                
                // perform a aabb testing
                if (!b1.Intersects2D(b2)) {
                    continue;
                }

                // get the shape in local coordinates
                const auto& t1 = c1->GetObject()->GetWorldTransform();
                const auto& t2 = c2->GetObject()->GetWorldTransform();
                //auto s1 = c1->GetShape()->transform(t1);
                //auto s2 = c2->GetShape()->transform(t2);


                // bounding boxes intersect, so let's make a proper collision test
                auto report = m_intersector->intersect(c1->GetShape(), c2->GetShape(), t1, t2);
                if (report.collide) {
                    CollisionInfo ci;
                    ci.report = report;
                    ci.pos = c.first;
                    currentlyCollidingPairs.insert(std::make_pair(std::make_pair(c1, c2), ci));
                }


            }
            // set cell as not dirty
            cell.dirty = false;
        }
    }
    // remove pairs that were previously colliding but not now
    for (auto iter = m_previouslyCollidingPairs.begin(); iter != m_previouslyCollidingPairs.end();) {
        CollisionInfo& ci = iter->second;
        // If i have examined the cell AND they are not colliding anymore ...
        if (cellsExamined.count(ci.pos) > 0 && currentlyCollidingPairs.count(iter->first) == 0) {
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

ShapeCastHit SpatialHashingCollisionEngine::ShapeCast (IShape* shape, const glm::mat4& transform, int mask) {
    ShapeCastHit result;
    auto aabb = shape->getBounds();
    aabb.Transform(transform);
    float z = transform[3][2];
    auto loc = getLocation(aabb);
    for (int i = loc.first.x; i <= loc.second.x; ++i) {
        for (int j = loc.first.y; j <= loc.second.y; ++j) {
            auto cell = m_cells.find(glm::vec2(i, j));
            if (cell != m_cells.end()) {
                auto &colliders = cell->second.colliders;
                for (auto &c : colliders) {
                    if (!c->isActive()) {
                        continue;
                    }
                    int flag = c->GetCollisionFlag();
                    int m = flag & mask;
                    if (m == 0) {
                        continue;
                    }
                    auto b = c->GetBounds();
                    // perform a aabb testing
                    if (!aabb.Intersects2D(b)) {
                        continue;
                    }
                    auto *s = c->GetShape();
                    if (s != nullptr) {
                        const auto &t = c->GetObject()->GetWorldTransform();
                        //auto s1 = s->transform(t);
                        //auto s2 = shape->transform(transform);
                        // bounding boxes intersect, so let's make a proper collision test
                        auto report = m_intersector->intersect(shape, s, transform, t);
                        if (report.collide) {
                         	Bounds bb = aabb.intersect(b);
                            result.report = report;
                            result.report.direction = glm::vec2(bb.GetCenter());
                            result.entity = c;
                            return result;
                        }
                    }
                }
            }
        }
    }
    return result;

}

RayCastHit SpatialHashingCollisionEngine::Raycast (glm::vec3 rayOrigin, glm::vec3 rayDir, float length, int mask, bool use_z) {

    glm::vec3 P = rayOrigin;
    glm::vec3 P1 = P;
    float z = rayOrigin.z;
    // initialize current cell
    int i = static_cast<int>(P.x / m_size.x);
    int j = static_cast<int>(P.y / m_size.y);
    //int k = (m_3d ? static_cast<int>(P.z / m_size.z) : 0);

    int n = (rayDir.x > 0 ? 1 : 0);
    int m = (rayDir.y > 0 ? 1 : 0);
    //int q = m_3d ? (rayDir.z > 0 ? 1 : 0) : 0;
    // n = 0 <-> r_x = 0 <-> vertical line
    // m = 0 <-> r_y = 0 <-> horizontal line
    float l = 0.0f;
    bool endReached = false;
	int id = 0, jd = 0, kd = 0;
    RayCastHit out;
    out.length = length;

    // we can (and we MUST) exit the loop as soon as we find a collision
    while (!endReached && !out.collide) {
        // get the next point into this cell
        // compute how much distance you need to cover to hit the cell boundary,
        // and what boundary you hit first (x, y or z)
        float tx = (rayDir.x == 0.0f) ? std::numeric_limits<float>::infinity() : ((i+n) * m_size.x - P.x) / rayDir.x;
        float ty = (rayDir.y == 0.0f) ? std::numeric_limits<float>::infinity() : ((j+m) * m_size.y - P.y) / rayDir.y;
        //float tz = (rayDir.z == 0.0f || !m_3d) ? std::numeric_limits<float>::infinity() : ((k+q) * m_size.z - P.z) / rayDir.z;
        float tm {0.0f};
        id = 0;
        jd = 0;
        //kd = 0;
        if (tx <= ty) {
        	tm = tx;
        	id = rayDir.x > 0 ? 1 : -1;
        } else {
        	tm = ty;
        	jd = rayDir.y > 0 ? 1 : -1;
        }

        // advance by tm
        if (l + tm < length) {
            // need to add a tiny extra bit in case the colliding object is a line that lies exactly at the border
            // of two neighboring cell!
            P1 = P + (tm+0.01f) * rayDir;
            // add tm to the cumulated length done
			l += tm;
        } else {
            P1 = P + (length - l) * rayDir;
            endReached = true;
        }

        // get the colliders at the current cell
        auto it = m_cells.find(glm::ivec2(i, j));
        Segment line (P, P1);
        auto lineBounds = line.getBounds();
        if (it != m_cells.end()) {
            for (auto& c : it->second.colliders) {
                if (!c->isActive())
                    continue;
                // aabb check
                int flag = c->GetCollisionFlag();
                int m = flag & mask;

                if (m != 0) {
                    auto shapeBounds = c->GetBounds();
                    if (lineBounds.Intersects2D(shapeBounds)) {
                        const auto& t = c->GetObject()->GetWorldTransform();
                        //auto cshape = c->GetShape()->transform(t);
                        //auto report = m_intersector->intersect(&line, cshape.get());
                        auto report = m_raycast->run(rayOrigin, rayDir, length, c->GetShape(), t);
                        if (report.collide && (!out.collide || out.length > report.length)) {
                            out.entity = c;
                            out.length = report.length;
                            out.collide = true;
                            out.normal = report.normal;
                        }
                    }
                }
            }
        }
        P = P1;
        // TODO move to next cell
        i += id;
        j += jd;
    }

    return out;

}




std::type_index SpatialHashingCollisionEngine::GetType() {
    return std::type_index(typeid(ICollisionEngine));
}
