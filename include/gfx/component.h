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

class Entity;

class Component : public Ref {
public:
    Component() : Ref(), m_active{true} {}
    //~ Component() {}
    // called once when the entity is added to the scene
    virtual void Start() = 0;
    virtual void Update(double) = 0;
    virtual void SetParent(Entity* parent) {
        m_entity = parent;
    }
    Entity* GetObject();
    bool IsActive();
    virtual void SetActive(bool);
protected:
    bool m_active;
    Entity* m_entity;
    
};

inline bool Component::IsActive() {
    return m_active;
}

inline void Component::SetActive(bool value) {
    m_active = value;
}


inline Entity* Component::GetObject() {
    return m_entity;
}

#endif /* component_h */
