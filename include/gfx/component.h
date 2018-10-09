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

class Entity;

class Component : public Ref {
public:
    Component() : Ref(), m_active{true} {}
    virtual ~ Component() {}
    // called once when the entity is added to the scene
    virtual void Start() = 0;
    virtual void Update(double) = 0;
    virtual void SetParent(Entity* parent) {
        m_entity = parent;
    }
    Entity* GetObject();
    bool IsActive() const;
    virtual bool SetActive(bool);
    virtual std::type_index GetType();
protected:
    bool m_active;
    Entity* m_entity;
    
};

inline bool Component::IsActive() const {
    return m_active;
}

inline bool Component::SetActive(bool value) {
    m_active = value;
    return true;
}


inline std::type_index Component::GetType() {
    return std::type_index(typeid(*this));
}

inline Entity* Component::GetObject() {
    return m_entity;
}

#endif /* component_h */
