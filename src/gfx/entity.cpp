//
//  entity.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//


#include "gfx/entity.h"
#include <gfx/engine.h>
#include <glm/gtx/transform.hpp>

using namespace std;

void Entity::AddChild(std::shared_ptr<Entity> child) {
    auto it = m_children.insert(m_children.end(), child);
    child->SetParent(this);
    child->m_itParent = it;
    //child->Notify(m_worldTransform);

    // if engine is running, start
    if (Engine::get().isRunning()) {
        child->Start();
    }
}

void Entity::Remove(Entity* entity) {
    m_children.erase(entity->m_itParent);

}

void Entity::ClearAllChildren() {

    for (auto& c : m_children) {
        Engine::get().Remove(c.get());
    }
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


void Entity::SetLocalTransform (glm::mat4 t) {
    m_localTransform = t;
    if (m_parent != nullptr)
        m_worldTransform = m_parent->GetWorldTransform() * m_localTransform;
    else
        m_worldTransform = m_localTransform;
    Notify ();
}

void Entity::SetWorldTransform(glm::mat4& wt) {
    m_worldTransform = wt * m_localTransform;
    Notify();
}

// to call whenever this change pos
void Entity::Notify() {
    //m_worldTransform = parentTransform * m_localTransform;
    for (auto& c : m_children)
        c->SetWorldTransform(m_worldTransform);

}

void Entity::SetPosition(glm::vec3 pos){
    SetLocalTransform(glm::translate(pos));
}

void Entity::SetPosition(glm::vec2 pos) {
    SetPosition(glm::vec3(pos.x, pos.y, m_localTransform[3][2]));
}

void Entity::SetParent(Entity* entity) {
    m_parent = entity;
    m_worldTransform = m_parent->GetWorldTransform() * m_localTransform;
    Notify();
}

void Entity::Move(glm::vec2 pos) {
    SetPosition(GetPosition() + glm::vec3(pos, 0.0f));
}