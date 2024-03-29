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
#include <monkey/components/renderer.h>
#include <monkey/scenefactory.h>

namespace py = pybind11;

using namespace std;




Entity::Entity(const ITab& t) : Ref(t),
    m_localTransform{glm::mat4(1.0)}, m_worldTransform{glm::mat4(1.0)}, m_parent(nullptr), m_flipHorizontal{false},
    m_enableControls{true}, m_update{true}
{
    auto pos = t.get<glm::vec3>("pos", glm::vec3(0.0f));
    if (t.has("angle")) {
        auto angle = t.get<float>("angle", 0.0f);
        SetPosition(pos, deg2rad* angle);
    } else {
        SetPosition(pos);
    }
    auto factory = Engine::get().GetSceneFactory();

    // let's see if this entity has a model
    if (t.has("model")) {

        auto model = factory->make2<Model>(*t["model"]);
        auto renderer = model->makeRenderer(model);

        AddComponent(model->makeRenderer(model, t));

    }

    if (t.has("transform")) {
    	m_localTransform = t.get<glm::mat4>("transform");
    }


	if (t.has("rotx")) {
		Rotate(glm::radians(t.get<float>("rotx")), glm::vec3(1.0f, 0.0f, 0.0f));
	}
    auto flipx = t.get<bool>("flip_x", false);
    SetFlipX(flipx);

    m_layer = t.get<int>("layer", 0);

    if (t.has("scale")) {
        auto scale = t.get<glm::vec3>("scale");
        setScale(scale);
    }


    if (t.has("camera")) {
        auto camt = t["camera"];
        auto camera = factory->make2<Camera>(*camt);
        camera->Init();
        SetCamera(camera);

    }

    // Add components ...
    t.foreach("components", [&] (const ITab& t) {
        AddComponent(factory->make2<Component>(t));
    });

    // ... and children
    t.foreach("children", [&] (const ITab& t) {
        AddChild(factory->make2<Entity>(t));
    });

    if (t.has("on_create")) {
    	t.get<pybind11::function>("on_create")(m_id, pos.x, pos.y, pos.z);
    }

}



Entity::~Entity() {
    if (!onDestroy.isEmpty()) {
        onDestroy.Fire(this);
    }
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
    int layer = child->getLayer();
    m_children[layer].push_back(child);
    m_iters[child->GetId()] = std::prev(m_children.at(layer).end());
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
    if (recursive) {
        for (const auto& layer : m_children) {
            for (auto& child : layer.second) {
                child->setActive(value);
            }
        }
    }
    SetActiveInnerCheck(value);
}


void Entity::Remove(Entity* entity) {
    //std::string name = entity->GetName();
    //if (!name.empty())
    //    m_namedChildren.erase(name);
    std::cerr << "removing " << entity->GetTag() << "\n";
    int layer = entity->getLayer();
    auto it = m_children.find(layer);
    if (it != m_children.end()) {
        entity->WindDown();
        it->second.erase(m_iters.at(entity->GetId()));
        //it->second.erase(entity->GetId());

    }

}

//Entity* Entity::GetNamedChild(const std::string& name) {
//    auto it = m_namedChildren.find(name);
//    if (it == m_namedChildren.end())
//        return nullptr;
//    return it->second;
//}

void Entity::ClearAllChildren() {

    for (const auto& layer : m_children) {
        for (auto& child : layer.second) {
            Engine::get().Remove(child.get());
        }
    }
}

std::map<int, std::list<std::shared_ptr<Entity>>>& Entity::GetChildren() {
    return m_children;
}

// update just calls update on each of the entity components
void Entity::Update(double dt) {
    if (!m_active || !m_update)
        return;
    for (auto& iter : m_components) {
        iter.second->Update(dt);
    }
    // now call update on children
    for (auto iter = m_children.rbegin(); iter != m_children.rend(); ++iter) {
        for (const auto& entity : iter->second) {
            entity->Update(dt);
        }
    }
}

void Entity::Start() {
    for (auto& iter : m_components) {
        iter.second->Start();
    }
    for (const auto& layer : m_children) {
        for (auto& child : layer.second) {
            child->Start();
        }
    }
}

void Entity::WindDown() {
    for (auto& iter : m_components) {
        iter.second->End();
    }
    for (const auto& layer : m_children) {
        for (auto& child : layer.second) {
            child->WindDown();
        }
    }
	if (!onRemove.isEmpty()) {
		onRemove.Fire(this);
	}

}

void Entity::Begin() {
    for (auto& iter : m_components) {
        iter.second->Begin();
    }
    for (const auto& layer : m_children) {
        for (auto& child : layer.second) {
            child->Begin();
        }
    }

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
//    std::stringstream  s ;
//    s << GetTag() << ": " ;
//    for (auto& c : m_children) {
//        std::string t = c.second->GetTag();
//        if (t.empty()) t = "*unknown*";
//        s << t << ", ";
//    }
//    s << "\n";
//    for (auto& c : m_children)
//        s << c.second->ToString();
//    return s.str();

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

    for (const auto& layer : m_children) {
        for (auto& child : layer.second) {
            child->SetWorldTransform(t);
        }
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
	float scale = GetScale();
    m_localTransform = glm::scale(glm::vec3(scale)) * glm::rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
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
    //std::cerr << "angle= " << angle << "\n";
    m_localTransform[0][0] = m_scale.x * (m_flipHorizontal ? -1 : 1) * m[0][0];
    m_localTransform[0][1] = m_scale.x * (m_flipHorizontal ? -1 : 1) * m[0][1];
    m_localTransform[1][0] = m_scale.y * m[1][0];
    m_localTransform[1][1] = m_scale.y * m[1][1];

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
    //std::cerr << "flipping from " << m_flipHorizontal << "\n";
    FlipX();
}

void Entity::setScale(glm::vec3 scale) {
    m_scale = scale;
    glm::vec3 i = glm::normalize(glm::vec3(m_localTransform[0]));
    glm::vec3 j = glm::normalize(glm::vec3(m_localTransform[1]));
    glm::vec3 k = glm::normalize(glm::vec3(m_localTransform[2]));
    i *= scale.x;
    j *= scale.y;
    k *= scale.z;
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

void Entity::SetScale(float s) {
    setScale(glm::vec3(s));

}

float Entity::GetScale() const {
    return glm::length(glm::vec3(m_localTransform[0]));
}

glm::vec3 Entity::getScaleVec() const {
    return m_scale;
}


void Entity::setOnMoveEnabled (bool value) {
    onMove.setEnabled(value);
    for (const auto& layer : m_children) {
        for (auto& child : layer.second) {
            child->onMove.setEnabled(value);
        }
    }

}

//std::string Entity::toString() {
//    std::stringstream stream;
//    stream << "[Entity](tag = " << m_tag << ", parent = " << (m_parent == nullptr ? "<root>" : std::to_string(m_parent->GetId())) << ")";
//    return stream.str();
//}
