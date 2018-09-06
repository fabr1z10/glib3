#include "gfx/collisionresponse.h"

CollisionHandler CollisionResponseManager::GetCollisionResponse(Collider* c1, Collider* c2) const {
    auto rm = m_response.find(std::make_pair(c1->GetTag(), c2->GetTag()));
    if (rm == m_response.end()) {
        rm = m_response.find(std::make_pair(c2->GetTag(), c1->GetTag()));
        if (rm == m_response.end()) {
            return CollisionHandler(rm->second.get(), true);
        }
        return CollisionHandler();
    } else {
        return CollisionHandler(rm->second.get(), false);
    }

};

void CollisionResponseManager::onStart (Collider* c1, Collider* c2, CollisionReport& report) {
    auto handler = GetCollisionResponse(c1, c2);
    if (handler.response != nullptr) {
        if (handler.flip) {
            report.direction *= -1.0f;
        }
        handler.response->onStart(c1->GetObject(), c2->GetObject(), report);
    }
}


void CollisionResponseManager::onStay (Collider* c1, Collider* c2, CollisionReport& report){
    auto handler = GetCollisionResponse(c1, c2);
    if (handler.response != nullptr) {
        if (handler.flip) {
            report.direction *= -1.0f;
        }
        handler.response->onStay(c1->GetObject(), c2->GetObject(), report);
    }
}

void CollisionResponseManager::onEnd (Collider* c1, Collider* c2, CollisionReport& report) {
    auto handler = GetCollisionResponse(c1, c2);
    if (handler.response != nullptr) {
        if (handler.flip) {
            report.direction *= -1.0f;
        }
        handler.response->onEnd(c1->GetObject(), c2->GetObject(), report);
    }

}


bool CollisionResponseManager::HasCollision(Collider * c1, Collider * c2) const {
    return (GetCollisionResponse(c1, c2).response != nullptr);
}

void CollisionResponseManager::AddCollisionResponse(int tag1, int tag2, std::unique_ptr<CollisionResponse> cr) {
    m_response.insert(std::make_pair(std::make_pair(tag1, tag2), std::move(cr)));
}