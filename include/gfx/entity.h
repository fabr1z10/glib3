//
//  entity.h
//  glib
//
//  Created by Fabrizio Venturini on 04/05/2018.
//
//

#ifndef entity_h
#define entity_h

#include <glm/glm.hpp>
#include <gfx/entity.h>
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
class Entity {
public:
    Entity() : m_parent(nullptr), m_active(true), m_localTransform{glm::mat4(1.0)}, m_worldTransform{glm::mat4(1.0)} {}
    ~Entity() {
        //onRemove.Fire(this);
    }
    const glm::mat4& GetLocalTransform() const;
    const glm::mat4& GetWorldTransform() const;
    std::string GetTag() const;
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
    
    void SetLayer(int);
    int GetLayer() const;
    //Event<GameObject*> onAdd;						// fires when a new node is added to this
    //Event<GameObject*> onMove;						// fires when this node moves
    //Event<GameObject*> onRemove;					// fires when this node goes out of scope
    // gets the world position
    glm::vec3 GetPosition() const;
    void SetLocalTransform (glm::mat4&);
    void SetPosition(glm::vec2&);
    void SetPosition(glm::vec3&);
    void Move(glm::vec2&);
    void Move(glm::vec3&);
    void Move(glm::mat4&);
    Entity* GetParent();
    bool IsActive() const;
    void SetActive(bool);
    glm::mat4& GetLastMove();
    //void AddRef(Ref* ref) {
    //	m_references.push_back(ref);
    //}
    //void EraseRef(Ref* ref) {
    //	m_references.remove(ref);
    //}
private:
    void Notify(glm::mat4& world);
    bool m_active;
    int m_layer;
    Entity* m_parent;
    std::list<std::shared_ptr<Entity> >::iterator m_itParent;
    std::list<std::shared_ptr<Entity> > m_children;
    std::string m_tag;
    glm::mat4 m_localTransform;
    glm::mat4 m_worldTransform;
    glm::mat4 m_lastMove;
    std::unordered_map<std::type_index, std::shared_ptr<Component> > m_components;
};

inline int Entity::GetLayer() const {
    return m_layer;
}

inline void Entity::SetLayer(int layer) {
    m_layer = layer;
}

inline glm::vec3 Entity::GetPosition() const {
    return glm::vec3(m_worldTransform[3]);
}

inline const glm::mat4& Entity::GetWorldTransform() const {
    return m_worldTransform;
}
#endif /* entity_h */
