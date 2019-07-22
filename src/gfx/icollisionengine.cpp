#include <gfx/icollisionengine.h>

ICollisionEngine::ICollisionEngine() : Runner(), m_responseManager(nullptr) {
}

void ICollisionEngine::SetResponseManager(std::unique_ptr<CollisionResponseManager> r){
    m_responseManager = std::move(r);
}

CollisionResponseManager* ICollisionEngine::GetResponseManager() {
    return m_responseManager.get();
}