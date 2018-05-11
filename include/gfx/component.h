//
//  component.h
//  glib
//
//  Created by Fabrizio Venturini on 04/05/2018.
//
//

#ifndef component_h
#define component_h

class Entity;

class Component {
public:
    Component() {}
    virtual~ Component() {}
    // called once when the entity is added to the scene
    virtual void Start() = 0;
    virtual void Update(double) = 0;
    void SetParent(Entity* parent) {
        m_entity = parent;
    }
    Entity* GetObject();
protected:
    Entity* m_entity;
    
};

inline Entity* Component::GetObject() {
    return m_entity;
}

#endif /* component_h */
