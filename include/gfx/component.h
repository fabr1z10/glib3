//
//  component.h
//  glib
//
//  Created by Fabrizio Venturini on 04/05/2018.
//
//

#ifndef component_h
#define component_h

#include <gfx/ref.h>
#include <typeindex>
#include <memory>

class Entity;

class Component : public Ref {
public:
    virtual ~ Component() {}
    // called once when the entity is added to the scene
    virtual void Start() = 0;
    // called once. When this is called, it is guaranteed that all other components have run the start method
    virtual void Begin() {}
    virtual void Update(double) = 0;
    virtual void SetParent(Entity* parent) {
        m_entity = parent;
    }
    Entity* GetObject();
    bool IsActive() const;
    virtual void SetActive(bool);
    virtual std::type_index GetType();
    virtual std::shared_ptr<Component> clone() const = 0;
protected:
    Component() : Ref(), m_active{true} {}
    Component(const Component&);

    bool m_active;
    Entity* m_entity;
    
};

inline bool Component::IsActive() const {
    return m_active;
}

inline void Component::SetActive(bool value) {
    m_active = value;
}


inline std::type_index Component::GetType() {
    return std::type_index(typeid(*this));
}

inline Entity* Component::GetObject() {
    return m_entity;
}

#endif /* component_h */
