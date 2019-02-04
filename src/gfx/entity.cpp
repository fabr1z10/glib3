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
#include <gfx/math/geom.h>

using namespace std;

void Entity::AddChild(std::shared_ptr<Entity> child) {
    auto it = m_children.insert(m_children.end(), child);
    child->SetParent(this);
    child->m_itParent = it;
    //child->Notify(m_worldTransform);

    std::string name = child->GetName();
    if (!name.empty()) {
        m_namedChildren[name] = child.get();
    }
    // if engine is running, start
    if (Engine::get().isRunning()) {
        child->Start();
        child->Begin();
    }
    onAdd.Fire(child.get());
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
    SetActiveInnerCheck(value);
}


void Entity::Remove(Entity* entity) {
    std::string name = entity->GetName();
    if (!name.empty())
        m_namedChildren.erase(name);
    m_children.erase(entity->m_itParent);

}

Entity* Entity::GetNamedChild(const std::string& name) {
    auto it = m_namedChildren.find(name);
    if (it == m_namedChildren.end())
        return nullptr;
    return it->second;
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

void Entity::Begin() {
    for (auto& iter : m_components) {
        iter.second->Begin();
    }
    for (auto& m : m_children)
        m->Begin();

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

void Entity::SetZ(float z) {
    m_localTransform[3][2] = z;
    UpdateWorldTransform();

}

void Entity::SetLocalTransform (glm::mat4 t) {
    m_localTransform = t;
    UpdateWorldTransform();
}

void Entity::UpdateWorldTransform() {
    if (m_parent != nullptr && m_parent->m_cameras == nullptr)
        m_worldTransform = m_parent->GetWorldTransform() * m_localTransform;
    else
        m_worldTransform = m_localTransform;         // identity if root or has camera
    Notify ();
    onMove.Fire(this);
}

void Entity::SetWorldTransform(glm::mat4& wt) {
    m_worldTransform = wt * m_localTransform;
    onMove.Fire(this);
    Notify();
}

// to call whenever this change pos
void Entity::Notify() {
    //m_worldTransform = parentTransform * m_localTransform;
    glm::mat4 t = m_cameras == nullptr ? m_worldTransform : glm::mat4(1.0f);
    for (auto& c : m_children) {
        c->SetWorldTransform(t);
    }

}

void Entity::SetPosition(glm::vec3 pos){
    m_localTransform[3][0] = pos.x;
    m_localTransform[3][1] = pos.y;
    m_localTransform[3][2] = pos.z;
    UpdateWorldTransform();
    //SetLocalTransform(glm::translate(pos));
    //onMove.Fire(this);
}

void Entity::SetPosition(glm::vec3 pos, float angle){
    m_localTransform = glm::rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
    m_localTransform[3][0] = pos.x;
    m_localTransform[3][1] = pos.y;
    m_localTransform[3][2] = pos.z;
    UpdateWorldTransform();
    //SetLocalTransform(glm::translate(pos)* glm::rotate(angle, glm::vec3(0,0,1)));
    //onMove.Fire(this);
}


void Entity::SetPosition(glm::vec2 pos) {
    SetPosition(glm::vec3(pos.x, pos.y, m_localTransform[3][2]));
}

void Entity::SetParent(Entity* entity) {
    m_parent = entity;
    if (m_parent->m_cameras == nullptr)
        m_worldTransform = m_parent->GetWorldTransform() * m_localTransform;
    else
        m_worldTransform = m_localTransform;
    Notify();
}

void Entity::MoveOrigin(glm::vec2 pos) {
    m_localTransform[3][0] += pos.x;
    m_localTransform[3][1] += pos.y;
    UpdateWorldTransform();
}

void Entity::MoveOrigin(glm::vec3 pos) {
    m_localTransform[3][0] += pos.x;
    m_localTransform[3][1] += pos.y;
    m_localTransform[3][2] += pos.z;
    UpdateWorldTransform();
}

void Entity::MoveLocal(glm::vec2 delta) {
    glm::vec2 worldDelta (m_worldTransform * glm::vec4(delta.x, delta.y, 0.0f, 0.0f));
    m_localTransform[3][0] += worldDelta.x;
    m_localTransform[3][1] += worldDelta.y;
    UpdateWorldTransform();
}

void Entity::RotateY(float deg) {
    glm::mat4 rot = glm::rotate(deg, glm::vec3(0,0,1));
    m_localTransform *= rot;
    UpdateWorldTransform();
}

void Entity::MoveLocal(glm::vec3 delta) {
    glm::vec3 worldDelta (m_worldTransform * glm::vec4(delta.x, delta.y, delta.z, 0.0f));
    m_localTransform[3][0] += worldDelta.x;
    m_localTransform[3][1] += worldDelta.y;
    m_localTransform[3][2] += worldDelta.z;
    UpdateWorldTransform();
}

Camera* Entity::GetCamera() {
    return m_cameras.get();
}

void Entity::SetAngle(float angle) {
    glm::mat4 m = glm::rotate(deg2rad * angle, glm::vec3(0,0,1));
    m_localTransform[0][0] = (m_flipHorizontal ? -1 : 1) * m[0][0];
    m_localTransform[0][1] = (m_flipHorizontal ? -1 : 1) * m[0][1];
    m_localTransform[1][0] = m[1][0];
    m_localTransform[1][1] = m[1][1];

    UpdateWorldTransform();
}

float Entity::GetAngle() const {
    if (m_localTransform[0][0] == 0.0)
        return m_localTransform[0][1] < 0 ? 90.0f : -90.0f;
    return rad2deg * atan(m_localTransform[0][1] / m_localTransform[0][0]);
}

void Entity::FlipX() {
    m_localTransform[0][0] *= -1.0f;
    m_localTransform[0][1] *= -1.0f;
    m_flipHorizontal = !m_flipHorizontal;
    UpdateWorldTransform();
}

void Entity::SetFlipX(bool value) {
    if (value == m_flipHorizontal)
        return;
    FlipX();
}

void Entity::SetScale(float s) {
    glm::vec3 i = glm::normalize(glm::vec3(m_localTransform[0]));
    glm::vec3 j = glm::normalize(glm::vec3(m_localTransform[1]));
    glm::vec3 k = glm::normalize(glm::vec3(m_localTransform[2]));
    i *= s;
    j *= s;
    k *= s;
    m_localTransform[0][0] = i.x;
    m_localTransform[0][1] = i.y;
    m_localTransform[0][2] = i.z;
    m_localTransform[1][0] = j.x;
    m_localTransform[1][1] = j.y;
    m_localTransform[1][2] = j.z;
    m_localTransform[2][0] = k.x;
    m_localTransform[2][1] = k.y;
    m_localTransform[2][2] = k.z;
    UpdateWorldTransform();


}
float Entity::GetScale() const {
    return glm::length(glm::vec3(m_localTransform[0]));
}