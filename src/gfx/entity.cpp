//
//  entity.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#include "gfx/entity.h"
#include <gfx/engine.h>

using namespace std;

void Entity::AddChild(std::shared_ptr<Entity> child) {
    auto it = m_children.insert(m_children.end(), child);
    child->m_parent = this;
    child->m_itParent = it;
    child->Notify(m_worldTransform);

    // if engine is running, start
    if (Engine::get().isRunning()) {
        child->Start();
    }
}

void Entity::Remove (Entity* child) {
    m_children.erase(child->m_itParent);
}

// update just calls update on each of the entity components
void Entity::Update(double dt) {
    if (!m_active)
        return;
    for (auto& iter : m_components) {
        iter.second->Update(dt);
    }
}

void Entity::Start() {
    for (auto& iter : m_components) {
        iter.second->Start();
    }
}


void Entity::SetLocalTransform (glm::mat4& t) {
    m_localTransform = t;
    Notify (m_worldTransform);
}

void Entity::Notify(glm::mat4& parentTransform) {
    m_worldTransform = parentTransform * m_localTransform;
    for (auto& c : m_children)
        c->Notify(m_worldTransform);

}