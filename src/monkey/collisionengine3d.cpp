#include <monkey/collisionengine3d.h>
#include <monkey/math/raycast.h>
#include <algorithm>

CollisionEngine3D::CollisionEngine3D (float dx, float dy, float dz) :
        ICollisionEngine(), m_width{dx}, m_height{dy}, m_depth(dz)
{
    m_intersector = std::unique_ptr<Intersector>(new Intersector);
}


glm::ivec3 CollisionEngine3D::getCell(glm::vec3 P) {
    glm::ivec3 coords;
    coords.x = P.x >= 0 ? static_cast<int>(P.x / m_width) : -1- static_cast<int>(abs(P.x)/m_width);
    coords.y = P.y >= 0 ? static_cast<int>(P.y / m_height) : -1- static_cast<int>(abs(P.y)/m_height);
    coords.z = P.z >= 0 ? static_cast<int>(P.z / m_depth) : -1- static_cast<int>(abs(P.z)/m_depth);
    return coords;
}

RayCastHit CollisionEngine3D::Raycast(glm::vec3 rayOrigin, glm::vec3 rayDir, float length, int mask, bool use_z) {
    //std::cerr << "just called " << rayDir.x << " " << rayDir.y << " " << rayDir.z << "\n";
    glm::vec3 P (rayOrigin);
    glm::vec3 P1 = P;

    // initialize current cell
    glm::ivec3 coords = getCell(P);
    int i = coords.x;
    int j = coords.y;
    int k = coords.z;
    // distance to h0it the vertical lines:
    // ((i+\xi)*delta - P) / u_x, where

    int n = (rayDir.x > 0 ? 1 : 0);
    int m = (rayDir.y > 0 ? 1 : 0);
    int p = (rayDir.z > 0 ? 1 : 0);

    float l = 0.0f;
    bool endReached = false;

    RayCastHit out;
    out.length = length;

    while (!endReached && !out.collide) {
        // get the next point into this cell
        float t1 = (rayDir.x == 0.0f) ? std::numeric_limits<float>::infinity() : ((i+n)*m_width - P.x) / rayDir.x;
        float t2 = (rayDir.y == 0.0f) ? std::numeric_limits<float>::infinity() : ((j+m)*m_height - P.y) / rayDir.y;
        float t3 = (rayDir.z == 0.0f) ? std::numeric_limits<float>::infinity() : ((k+p)*m_depth - P.z) / rayDir.z;
        float tm = std::min({t1, t2, t3});

        if (l + tm < length) {
            // need to add a tiny extra bit in case the colliding object is a line that lies exactly at the border
            // of two neighboring cell!
            P1 = P + (tm+0.01f) * rayDir;
        } else {
            P1 = P + length * rayDir;
            endReached = true;
        }

        // get the colliders at the current cell
        auto it = m_cells.find(glm::ivec3(i, j, k));
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
                    //float zc = c->GetObject()->GetPosition().z;

                    auto shapeBounds = c->GetBounds();
                    if (lineBounds.Intersects(shapeBounds)) {
                        auto t = c->GetObject()->GetWorldTransform();
                        //std::cerr << "abc " << rayDir.x << " " <<rayDir.y << " " << rayDir.z << " " << length << "\n";
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
            if (t1 < t3) {
                i += (rayDir.x > 0 ? 1 : -1);
            } else {
                k += (rayDir.z > 0 ? 1 : -1);
            }
        } else {
            if (t2 < t3) {
                j += (rayDir.y > 0 ? 1 : -1);
            } else {
                k += (rayDir.z > 0 ? 1 : -1);
            }
        }

    }
//    if (out.collide) {
//        std::cout << "Collide! length = " << out.length << "\n";
//    }
    return out;

}


ShapeCastHit CollisionEngine3D::ShapeCast (std::shared_ptr<Shape> shape, const glm::mat4& transform, int mask) {
    ShapeCastHit result;
    auto aabb = shape->getBounds();
    aabb.Transform(transform);
    float z = transform[3][2];
    Location3D loc = GetLocation(aabb);
    for (int i = loc.x0; i <= loc.x1; ++i) {
        for (int j = loc.y0; j <= loc.y1; ++j) {
            for (int k = loc.z0; k <= loc.z1; ++k) {
                auto cell = m_cells.find(glm::ivec3(i, j, k));
                if (cell != m_cells.end()) {
                    auto &colliders = cell->second.colliders;
                    for (auto &c : colliders) {
                        int flag = c->GetCollisionFlag();
                        int m = flag & mask;
                        if (m == 0) {
                            continue;
                        }
                        auto b = c->GetBounds();
                        // perform a aabb testing
                        if (!aabb.Intersects(b)) {
                            continue;
                        }
                        Shape *s = c->GetShape();
                        auto &t = c->GetObject()->GetWorldTransform();

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
    }
    return result;

}

void CollisionEngine3D::Add(ICollider* c) {
    // this is called when a new collider starts. It registers with the engine
    // get the shape bounding box, transform it, map it
    auto aabb = c->GetBounds();
    if (!aabb.isVoid()) {
        Location3D loc = GetLocation(aabb);
        PushCollider(c, loc);
    }


}

void CollisionEngine3D::Remove(ICollider* c) {
    // called when a collider dies
    PopCollider(c);
}

void CollisionEngine3D::Clear() {
    m_cells.clear();
    m_colliderLocations.clear();
    m_previouslyCollidingPairs.clear();
}

void CollisionEngine3D::helperLoc(float x0, float x1, int &a, int &b, float size) {
    a = floor (x0 / size);
    float mx = x1 / size;
    int imx = floor(mx);
    if (imx == a+1 && (mx - imx == 0.0f)) imx--;
    b = imx;

}

void CollisionEngine3D::Move(ICollider * c) {

    auto it = m_colliderLocations.find(c);
    if (it != m_colliderLocations.end()) {
        auto aabb = c->GetBounds();
        Location3D loc = GetLocation(aabb);
        if (it->second != loc) {
            //std::cout << "Collider " << c->GetShape()->toString() << " moved to loc from (" << loc.x0 << ", " << loc.y0 << ") to (" << loc.x1 << ", " << loc.y1 << ")\n";
            if (loc != it->second) {
                // if it's still in the same region nbothing to do
                PopCollider(c);
                PushCollider(c, loc);
            }
        }
        else {
            // if the entity is still in the same cell range, I still need to make them dirty
            for (int i = loc.x0; i <= loc.x1; ++i) {
                for (int j = loc.y0; j <= loc.y1; ++j) {
                    for (int k = loc.z0; k<=loc.z1; ++k) {
                        auto &cell = m_cells[glm::ivec3(i, j, k)];
                        cell.dirty = true;
                    }
                }
            }
        }
    } else {
        Add(c);
    }

}

Location3D CollisionEngine3D::GetLocation(const Bounds& aabb) {
    //auto aabb = c->GetBounds();
    Location3D loc;
    helperLoc(aabb.min.x, aabb.max.x, loc.x0, loc.x1, m_width);
    helperLoc(aabb.min.y, aabb.max.y, loc.y0, loc.y1, m_height);
    helperLoc(aabb.min.z, aabb.max.z, loc.z0, loc.z1, m_depth);
    return loc;
}

void CollisionEngine3D::PushCollider(ICollider* c, Location3D loc) {
    for (int i = loc.x0; i <= loc.x1; ++i) {
        for (int j = loc.y0; j <= loc.y1; ++j) {
            for (int k = loc.z0; k <= loc.z1; ++k) {
                auto &cell = m_cells[glm::ivec3(i, j, k)];
                cell.colliders.insert(c);
                cell.dirty = true;
            }
        }
    }
    m_colliderLocations[c] = loc;
}
void CollisionEngine3D::PopCollider(ICollider* c) {

    auto it = m_colliderLocations.find(c);
    if (it != m_colliderLocations.end()) {
        Location3D loc = it->second;
        for (int i = loc.x0; i <= loc.x1; ++i) {
            for (int j = loc.y0; j <= loc.y1; ++j) {
                for (int k = loc.z0; k <= loc.z1; ++k) {
                    auto &cell = m_cells[glm::ivec3(i, j, k)];
                    cell.colliders.erase(c);
                    cell.dirty = true;
                }
            }
        }

    }
}
void CollisionEngine3D::Update(double dt) {

    // loop throught all dirty cells and do a pair-wise collision detection for each collider within the cell.
//    std::unordered_map<std::pair<ICollider*, ICollider*>, CollisionInfo> currentlyCollidingPairs;
//    //std::cout << "Running collision engine update...\n";
//    std::unordered_set<std::pair<int, int>> cellsExamined;
//    //std::unordered_set<std::pair<Collider*, Collider*>> testedPairs;
//    for (auto& cell : m_cells) {
//        // skip cells that have less than 2 colliders
//        if (!cell.second.dirty)
//            continue;
//        cellsExamined.insert(std::make_pair(cell.first.first, cell.first.second));
//        if (cell.second.colliders.size() < 2)
//        {
//            cell.second.dirty = false;
//            continue;
//        }
//        //std::cout << "Examining cell " << cell.first.first << ", " << cell.first.second << "\n";
//        for (auto iter = cell.second.colliders.begin(); iter != cell.second.colliders.end(); ++iter) {
//            ICollider* c1 = *iter;
//            if (!c1->isActive())
//                continue;
//            float z1 = c1->GetObject()->GetPosition().z;
//            auto iter2 = iter;
//            for (++iter2; iter2 != cell.second.colliders.end(); ++iter2) {
//                ICollider * c2 = *iter2;
//                float z2 = c2->GetObject()->GetPosition().z;
//                if (!c2->isActive())
//                    continue;
//                // check collision mask
//                if ( ((c1->GetCollisionMask() & c2->GetCollisionFlag()) == 0) && ((c2->GetCollisionMask() & c1->GetCollisionFlag()) == 0)) {
//                    // If at least one mask is hit, then we keep checking the collision.
//                    // if both mask fail, then we skip to the next collider
//                    continue;
//                }
//
//                // if no response is provided for these tags, then skip it
//                if (m_responseManager == nullptr || !m_responseManager->HasCollision(c1, c2)) {
//                    //std::cout << "No response for tag (" << c1->GetTag() << ", " << c2->GetTag() << ")\n";
//                    continue;
//                }
//                // 2.5d collision check
//                if (m_coll25d && fabs(z1-z2) > m_eps) {
//                    continue;
//                }
//
//
//                // we have a collision response, so let's calculate collision
//                auto b1 = c1->GetBounds();
//                auto b2 = c2->GetBounds();
//
//                // perform a aabb testing
//                if (!b1.Intersects(b2)) {
//                    //std::cout << "aabb do not intersect\n";
//                    continue;
//                }
//                //std::cout << "aabb do intersect. Now do a proper testing\n";
//                Shape* s1 = c1->GetShape();
//                Shape* s2 = c2->GetShape();
//                auto& t1 = c1->GetObject()->GetWorldTransform();
//                auto& t2 = c2->GetObject()->GetWorldTransform();
//
//                // bounding boxes intersect, so let's make a proper collision test
//                CollisionReport report = m_intersector->Intersect(s1, t1, s2, t2);
//                //std::cout << "COllide = " << report.collide << "\n";
//                if (report.collide) {
//                    CollisionInfo ci;
//                    ci.report = report;
//                    ci.i = cell.first.first;
//                    ci.j = cell.first.second;
//                    currentlyCollidingPairs.insert(std::make_pair(std::make_pair(c1, c2), ci));
//                }
//
//
//            }
//            // set cell as not dirty
//            cell.second.dirty = false;
//        }
//    }
//    // remove pairs that were previously colliding but not now
//    for (auto iter = m_previouslyCollidingPairs.begin(); iter != m_previouslyCollidingPairs.end();) {
//        CollisionInfo& ci = iter->second;
//        // If i have examined the cell AND they are not colliding anymore ...
//        if (cellsExamined.count(std::make_pair(ci.i, ci.j))>0 && currentlyCollidingPairs.count(iter->first) == 0) {
//            m_responseManager->onEnd (iter->first.first, iter->first.second, ci.report);
//            m_previouslyCollidingPairs.erase(iter++);
//        }
//        else {
//            iter++;
//        }
//    }
//
//    for (auto& p : currentlyCollidingPairs) {
//        auto it = m_previouslyCollidingPairs.find(p.first);
//        if (it == m_previouslyCollidingPairs.end()) {
//            m_responseManager->onStart (p.first.first, p.first.second, p.second.report);
//            m_previouslyCollidingPairs.insert(std::make_pair(p.first, p.second));
//        } else {
//            m_responseManager->onStay(p.first.first, p.first.second, p.second.report);
//            it->second = p.second;
//        }
//    }

    // add the new collision pairs
}

std::type_index CollisionEngine3D::GetType() {
    return std::type_index(typeid(ICollisionEngine));
}

std::string CollisionEngine3D::toString() {
    std::stringstream stream;
    stream << "[CollisionEngine3D](tag = " << m_tag << ", size = (" << m_width << ", " << m_height << ", " << m_depth << "))";
    return stream.str();
}