//
//  entity.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//


#include <monkey/entity.h>
#include <monkey/engine.h>
#include <glm/gtx/transform.hpp>
#include <monkey/math/geom.h>

using namespace std;

Entity::Entity(const LuaTable & t) : Ref(t),
    m_localTransform{glm::mat4(1.0)}, m_worldTransform{glm::mat4(1.0)}, m_parent(nullptr), m_flipHorizontal{false},  m_enableControls{true}
{

    glm::vec3 pos = t.Get<glm::vec3>("pos", glm::vec3(0.0f));
    if (t.HasKey("angle")) {
        float angle = t.Get<float>("angle", 0.0f);
        SetPosition(pos, deg2rad* angle);
    } else {
        SetPosition(pos);
    }

    bool flipx = t.Get<bool>("flipx", false);
    SetFlipX(flipx);

    if (t.HasKey("scale")) {
        float scale = t.Get<float>("scale");
        SetScale(scale);
    }

    auto factory = Engine::get().GetSceneFactory();

    // setup camera, if any
    if (t.HasKey("camera")) {
        LuaTable tc = t.Get<LuaTable>("camera");
        auto camera = factory->make<Camera>(tc);
        SetCamera(camera);
    }

    // add components
    t.ProcessVector("components", [&] (luabridge::LuaRef ref) {
        LuaTable tc(ref);
        AddComponent(factory->make<Component>(tc));
    });

    t.ProcessVector("children", [&] (luabridge::LuaRef ref) {
        LuaTable tc(ref);
        AddChild(factory->make<Entity>(tc));
    });

}

Entity::Entity(const Entity & e) : Ref(e), m_update(e.m_update) {
    m_flipHorizontal = e.m_flipHorizontal;
    m_active = e.m_active;
    m_enableControls = e.m_enableControls;
    m_localTransform = e.m_localTransform;
    m_worldTransform = glm::mat4(1.0f);
    for (auto& c : e.m_children) {
        // this will set the children parents and this' named children
        this->AddChild(c.second->clone());
    }
    for (auto& comp : e.m_components) {
        this->AddComponent(comp.second->clone());
    }

}

Entity::~Entity() {
    if (!onDestroy.isEmpty()) {
        onDestroy.Fire(this);
    }
}

std::shared_ptr<Entity> Entity::clone() const {
    return std::make_shared<Entity>(*this);


}

// make sure start is called only once!!!
void Entity::start() {
    if (m_started) {
        return;
    }
    m_started = true;
    Start();

}

void Entity::restart() {
    m_started = false;
    Start();
}

void Entity::AddChild(std::shared_ptr<Entity> child) {
    m_children.insert(std::make_pair(child->GetId(), child));
    child->SetParent(this);

    std::string name = child->GetName();
    if (!name.empty()) {
        m_namedChildren[name] = child->GetId();
    }
    // if engine is running, start
    child->UpdateWorldTransform();
    onAdd.Fire(child.get());
    if (Engine::get().isRunning()) {
        child->Start();
        child->Begin();
    }

}



void Entity::setActive(bool value) {
    Ref::setActive(value);
    bool recursive = true;
    for (auto& h : m_components) {
        h.second->setActive(value);
    }
    // now call setActive on all children
    if (recursive)
        for (auto& c: m_children)
            c.second->setActive(value);
    SetActiveInnerCheck(value);
}


void Entity::Remove(int id) {
    //std::string name = entity->GetName();
    //if (!name.empty())
    //    m_namedChildren.erase(name);
    auto entity = m_children.at(id);
    entity->WindDown();
    if (!onRemove.isEmpty()) {
        onRemove.Fire(entity.get());
    }
    m_children.erase(id);

}

//Entity* Entity::GetNamedChild(const std::string& name) {
//    auto it = m_namedChildren.find(name);
//    if (it == m_namedChildren.end())
//        return nullptr;
//    return it->second;
//}

void Entity::ClearAllChildren() {

    for (auto& c : m_children) {
        Engine::get().Remove(c.second);
    }
}

std::unordered_map<int, std::shared_ptr<Entity> >& Entity::GetChildren() {
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
    for (auto& m : m_children) {
        m.second->Start();
    }
}

void Entity::WindDown() {
    for (auto& iter : m_components) {
        iter.second->End();
    }
    for (auto& child : m_children) {
        child.second->WindDown();
    }

}

void Entity::Begin() {
    for (auto& iter : m_components) {
        iter.second->Begin();
    }
    for (auto& m : m_children)
        m.second->Begin();

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
        std::string t = c.second->GetTag();
        if (t.empty()) t = "*unknown*";
        s << t << ", ";
    }
    s << "\n";
    for (auto& c : m_children)
        s << c.second->ToString();
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
    if (m_parent != nullptr) // && m_parent->m_cameras == nullptr)
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
        c.second->SetWorldTransform(t);
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

void Entity::Rotate(float angle, glm::vec3 axis) {
    m_localTransform *= glm::rotate(angle, axis);
    UpdateWorldTransform();

}


void Entity::SetPosition(glm::vec2 pos) {
    SetPosition(glm::vec3(pos.x, pos.y, m_localTransform[3][2]));
}

void Entity::SetParent(Entity* entity) {
    m_parent = entity;
    // if (m_parent->m_cameras == nullptr)
    m_worldTransform = m_parent->GetWorldTransform() * m_localTransform;
    //else
    //m_worldTransform = m_localTransform;
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


void Entity::setOnMoveEnabled (bool value) {
    onMove.setEnabled(value);
    for (const auto& c : m_children) c.second->onMove.setEnabled(value);

}

std::string Entity::toString() {
    std::stringstream stream;
    stream << "[Entity](tag = " << m_tag << ", parent = " << (m_parent == nullptr ? "<root>" : std::to_string(m_parent->GetId())) << ")";
    return stream.str();
}
