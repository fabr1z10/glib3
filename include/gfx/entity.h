//
//  entity.h
//  glib
//
//  Created by Fabrizio Venturini on 04/05/2018.
//
//

#ifndef entity_h
#define entity_h

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <gfx/enums.h>
#include <gfx/ref.h>
#include <gfx/camera.h>
#include <gfx/iterator.h>
#include <gfx/component.h>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <list>
#include <memory>
#include <unordered_map>

/// An entity (aka node) has a position, a tag and a bunch of components attached
/// that determine its behaviour. Every entity can have zero or more children entities
/// and only one parent (i.e. they are organized in a tree)
class Entity : public Ref {
public:
    Entity() : Ref(), m_parent(nullptr), m_update(true), m_localTransform{glm::mat4(1.0)},
               m_worldTransform{glm::mat4(1.0)}, m_enableControls{true}, m_flipHorizontal{false} {}
    // copy ctor
    Entity(const Entity&);

    //static std::shared_ptr<Entity> Create ();

    const glm::mat4& GetLocalTransform() const;
    const glm::mat4& GetWorldTransform() const;

    std::string ToString();

    template <class C>
    void AddComponent(std::shared_ptr<C> c) {
        m_components[c->GetType()] = c;
        c->SetParent(this);
    }
    template <class T>
    T* GetComponent() {
        auto it = m_components.find(std::type_index(typeid(typename T::ParentClass)));
        if (it != m_components.end()) {
            return dynamic_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    virtual std::shared_ptr<Entity> clone() const;


    void AddChild(std::shared_ptr<Entity>);
    void ClearAllChildren();
    std::unordered_map<int, std::shared_ptr<Entity> >& GetChildren();
    void Remove(int);
    void Update(double);
    virtual void Start();
    void WindDown();
    void Begin();
    friend class DepthFirstIterator<Entity>;
    DepthFirstIterator<Entity> begin() {
        return DepthFirstIterator<Entity>(this);
    }
    DepthFirstIterator<Entity> end() {
        return DepthFirstIterator<Entity>();
    }
    bool IsDescendantOf (Entity*) const;
    

    Event<Entity*> onMove;						// fires when this node moves
    Event<Entity*> onAdd;
    Event<Entity*> onRemove;
    //Event<GameObject*> onRemove;					// fires when this node goes out of scope

    // gets the world position
    glm::vec3 GetPosition() const;
    void SetLocalTransform (glm::mat4);
    void SetZ(float);


    // set the position of the local origin in w.c.
    void SetPosition(glm::vec2);
    void SetPosition(glm::vec3);
    void SetPosition(glm::vec3, float angle);

    // move the origin by a given amount
    void MoveOrigin(glm::vec2);
    void MoveOrigin(glm::vec3);
    void MoveLocal(glm::vec2);
    void MoveLocal(glm::vec3);
    void RotateY(float deg);
    //void MoveOrigin(glm::mat4&);



    // set angle (around z-axis) in degrees
    void SetAngle(float);
    float GetAngle() const;

    std::string GetName() const;
    void SetName(const std::string& name);
    //Entity* GetParent();

    // an active entity gets updated at every frame,
    // and responds to events (i.e. hot-spots)
    // bool IsActive() const;
    void setActive(bool) override;
    void SetEnableUpdate(bool);
    bool IsUpdateEnabled() const;

    // invert current flip
    void FlipX();
    // set flip horizontal (true = facing left)
    void SetFlipX(bool);
    bool GetFlipX() const;
    float GetScale() const;
    void SetScale(float);

    bool AreControlsEnabled() const;
    void SetControlsEnabled(bool);
    glm::mat4& GetLastMove();
    //void AddRef(Ref* ref) {
    //	m_references.push_back(ref);
    //}
    //void EraseRef(Ref* ref) {
    //	m_references.remove(ref);
    //}
    Entity* GetParent() const { return m_parent;}
    void SetParent(Entity*);
    void SetCamera(std::shared_ptr<Camera>);
    Camera* GetCamera();
    //Entity* GetNamedChild(const std::string& name);
    void setOnMoveEnabled (bool);
    std::string toString() override;
protected:

private:
    void UpdateWorldTransform();
    void SetWorldTransform(glm::mat4& wt);
    void Notify();
    virtual void SetActiveInnerCheck(bool) {}
    bool m_flipHorizontal;
    //bool m_active;
    bool m_update;
    bool m_enableControls;
    //int m_layer;
    Entity* m_parent;
    //std::list<std::shared_ptr<Entity> >::iterator m_itParent;
    //std::list<std::shared_ptr<Entity> > m_children;
    std::unordered_map<int, std::shared_ptr<Entity> > m_children;

    glm::mat4 m_localTransform;
    glm::mat4 m_worldTransform;
    std::unordered_map<std::type_index, std::shared_ptr<Component> > m_components;
    // can also be a vec of cameras?
    std::shared_ptr<Camera> m_cameras;
    std::string m_name;
    std::unordered_map<std::string, int> m_namedChildren;
};

//inline int Entity::GetLayer() const {
//    return m_layer;
//}
//
//inline void Entity::SetLayer(int layer) {
//    m_layer = layer;
//    for (auto& c : m_children)
//        c->SetLayer(layer);
//}

inline glm::vec3 Entity::GetPosition() const {
    return glm::vec3(m_worldTransform[3]);
}

inline const glm::mat4& Entity::GetWorldTransform() const {
    return m_worldTransform;
}
inline const glm::mat4& Entity::GetLocalTransform() const {
    return m_localTransform;
}
inline void Entity::SetCamera(std::shared_ptr<Camera> cam)  {
    m_cameras = cam;
}

inline bool Entity::AreControlsEnabled() const {
    return m_enableControls;
}

inline void Entity::SetControlsEnabled(bool value) {
    m_enableControls = value;
}

inline void Entity::SetEnableUpdate(bool value){
    m_update = value;
    for (auto& c : m_children)
        c.second->SetEnableUpdate(value);
}

inline bool Entity::IsUpdateEnabled() const {
    return m_update;
}

inline void Entity::SetName(const std::string& name) {
    m_name =name;
}

inline std::string Entity::GetName() const {
    return m_name;
}

inline bool Entity::GetFlipX() const {
    return m_flipHorizontal;
}

#endif /* entity_h */
