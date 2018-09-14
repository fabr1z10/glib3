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


bool Entity::IsActive() const {
    return m_active;
}

void Entity::SetActive(bool value) {
    m_active = value;
    bool recursive = true;
    for (auto& h : m_components) {
        recursive = h.second->SetActive(value);
    }
    // now call setActive on all children
    if (recursive)
        for (auto& c: m_children)
            c->SetActive(value);

}


void Entity::Remove(Entity* entity) {
    m_children.erase(entity->m_itParent);

}

void Entity::ClearAllChildren() {

    for (auto& c : m_children) {
        Engine::get().Remove(c.get());
    }
}

 std::list<std::shared_ptr<Entity> >& Entity::GetChildren() {
    return m_children;
}

// update just calls update on each of the entity components
void Entity::Update(double dt) {
    if (!m_active || !m_update)
        return;
    for (auto& iter : m_components) {
        iter.second->Update(dt);
    }
}

void Entity::Start() {
    for (auto& iter : m_components) {
        iter.second->Start();
    }
    for (auto& m : m_children)
        m->Start();

}


bool Entity::IsDescendantOf(Entity * other) const {
    Entity* current = GetParent();
    while (current != nullptr) {
        if (current == other)
            return true;
        current = current->GetParent();
    }
    return false;
}


std::string Entity::ToString() {
    std::stringstream  s ;
    s << GetTag() << ": " ;
    for (auto& c : m_children) {
        std::string t = c->GetTag();
        if (t.empty()) t = "*unknown*";
        s << t << ", ";
    }
    s << "\n";
    for (auto& c : m_children)
        s << c->ToString();
    return s.str();

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
    onMove.Fire(this);
}

void Entity::SetPosition(glm::vec3 pos, float angle){
    SetLocalTransform(glm::translate(pos)* glm::rotate(angle, glm::vec3(0,0,1)));
    onMove.Fire(this);
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

Camera* Entity::GetCamera() {
    return m_cameras.get();
}