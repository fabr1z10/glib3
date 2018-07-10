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

// an entity has a position, a tag and a bunch of components attached
// that determine its behaviour. Every entity can have zero or more children entities
// and only one parent (i.e. they are organized in a tree)
class Entity : public Ref {
public:
    Entity() : Ref(), m_parent(nullptr), m_active(true), m_localTransform{glm::mat4(1.0)}, m_worldTransform{glm::mat4(1.0)}, m_enableControls{true} {}

    const glm::mat4& GetLocalTransform() const;
    const glm::mat4& GetWorldTransform() const;

    std::string ToString();

    template <class C>
    void AddComponent(std::shared_ptr<C> c) {
        m_components[std::type_index(typeid(typename C::ParentClass))] = c;
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
    void AddChild(std::shared_ptr<Entity>);
    void ClearAllChildren();
    std::list<std::shared_ptr<Entity> >& GetChildren();
    void Remove(Entity*);
    void Update(double);
    void Start();
    friend class DepthFirstIterator<Entity>;
    DepthFirstIterator<Entity> begin() {
        return DepthFirstIterator<Entity>(this);
    }
    DepthFirstIterator<Entity> end() {
        return DepthFirstIterator<Entity>();
    }
    bool IsDescendantOf (Entity*) const;
    
    void SetLayer(int);
    int GetLayer() const;
    //Event<GameObject*> onAdd;						// fires when a new node is added to this
    Event<Entity*> onMove;						// fires when this node moves
    //Event<GameObject*> onRemove;					// fires when this node goes out of scope
    // gets the world position
    glm::vec3 GetPosition() const;
    void SetLocalTransform (glm::mat4);
    void SetPosition(glm::vec2);
    void SetPosition(glm::vec3);
    void Move(glm::vec2);
    void Move(glm::vec3&);
    void Move(glm::mat4&);
    //Entity* GetParent();

    // an active entity gets updated at every frame,
    // and responds to events (i.e. hot-spots)
    bool IsActive() const;
    void SetActive(bool);



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
    void SetCamera(std::unique_ptr<Camera>);
    Camera* GetCamera();
private:
    void SetWorldTransform(glm::mat4& wt);
    void Notify();
    bool m_active;
    bool m_enableControls;
    int m_layer;
    Entity* m_parent;
    std::list<std::shared_ptr<Entity> >::iterator m_itParent;
    std::list<std::shared_ptr<Entity> > m_children;
    glm::mat4 m_localTransform;
    glm::mat4 m_worldTransform;
    glm::mat4 m_lastMove;
    std::unordered_map<std::type_index, std::shared_ptr<Component> > m_components;
    // can also be a vec of cameras?
    std::unique_ptr<Camera> m_cameras;

};

inline int Entity::GetLayer() const {
    return m_layer;
}

inline void Entity::SetLayer(int layer) {
    m_layer = layer;
    for (auto& c : m_children)
        c->SetLayer(layer);
}

inline glm::vec3 Entity::GetPosition() const {
    return glm::vec3(m_worldTransform[3]);
}

inline const glm::mat4& Entity::GetWorldTransform() const {
    return m_worldTransform;
}

inline void Entity::SetCamera(std::unique_ptr<Camera> cam)  {
    m_cameras = std::move(cam);
}

inline bool Entity::AreControlsEnabled() const {
    return m_enableControls;
}

inline void Entity::SetControlsEnabled(bool value) {
    m_enableControls = value;
}


#endif /* entity_h */
