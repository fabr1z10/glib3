#include <monkey/collisionresponse.h>

CollisionHandler CollisionResponseManager::GetHandler(int tag1, int tag2) {

    auto rm = m_response.find(std::make_pair(tag1, tag2));
    if (rm == m_response.end()) {
        rm = m_response.find(std::make_pair(tag2, tag1));
        if (rm != m_response.end()) {
            return CollisionHandler(rm->second.get(), true);
        }
        return CollisionHandler();
    } else {
        return CollisionHandler(rm->second.get(), false);
    }

}

CollisionHandler CollisionResponseManager::GetCollisionResponse(ICollider* c1, ICollider* c2) const {
    auto rm = m_response.find(std::make_pair(c1->GetCollisionTag(), c2->GetCollisionTag()));
    if (rm == m_response.end()) {
        rm = m_response.find(std::make_pair(c2->GetCollisionTag(), c1->GetCollisionTag()));
        if (rm != m_response.end()) {
            return CollisionHandler(rm->second.get(), true);
        }
        return CollisionHandler();
    } else {
        return CollisionHandler(rm->second.get(), false);
    }

};

void CollisionResponseManager::onStart (ICollider* c1, ICollider* c2, CollisionReport& report) {
    auto handler = GetCollisionResponse(c1, c2);
    if (handler.response != nullptr) {
        if (handler.flip) {
            report.direction *= -1.0f;
            handler.response->onStart(c2->GetObject(), c1->GetObject(), report);
        } else {
            handler.response->onStart(c1->GetObject(), c2->GetObject(), report);
        }
    }
}


void CollisionResponseManager::onStay (ICollider* c1, ICollider* c2, CollisionReport& report){
    auto handler = GetCollisionResponse(c1, c2);
    if (handler.response != nullptr) {
        if (handler.flip) {
            report.direction *= -1.0f;
            handler.response->onStay(c2->GetObject(), c1->GetObject(), report);
        } else {
            handler.response->onStay(c1->GetObject(), c2->GetObject(), report);
        }
    }
}

void CollisionResponseManager::onEnd (ICollider* c1, ICollider* c2, CollisionReport& report) {
    auto handler = GetCollisionResponse(c1, c2);
    if (handler.response != nullptr) {
        if (handler.flip) {
            report.direction *= -1.0f;
            handler.response->onEnd(c2->GetObject(), c1->GetObject(), report);
        } else {
            handler.response->onEnd(c1->GetObject(), c2->GetObject(), report);
        }
    }

}


bool CollisionResponseManager::HasCollision(ICollider * c1, ICollider * c2) const {
    return (GetCollisionResponse(c1, c2).response != nullptr);
}

void CollisionResponseManager::AddCollisionResponse(int tag1, int tag2, std::unique_ptr<CollisionResponse> cr) {
    m_response.insert(std::make_pair(std::make_pair(tag1, tag2), std::move(cr)));
}