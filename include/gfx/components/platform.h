#pragma once

#include <gfx/component.h>
#include <gfx/components/controller2d.h>
#include <gfx/event.h>
#include <set>
#include <memory>

// the platform component registers with the move event
// on its game object. Therefore, when the game object moves, this triggers
// a corresponding move on its registered objects
class PlatformComponent : public Component {
public:
    PlatformComponent() : Component() {}
    virtual ~PlatformComponent();
    void Move(Entity*);
    virtual void Start();
    virtual void Update(double) {}
    virtual void Register(Controller2D*);
    virtual void Unregister(Controller2D*);
    virtual void UnregisterAll();
    std::set<Controller2D*>::iterator begin() {
        return m_characters.begin();
    }
    std::set<Controller2D*>::iterator end() {
        return m_characters.end();
    }
    using ParentClass = PlatformComponent;
    std::set<Controller2D*>& GetCharacters() {
        return m_characters;
    }
protected:
    //EventListener m_listener;
    Controller2D* m_current;
    std::set<Controller2D*> m_characters;
};


inline void PlatformComponent::Register(Controller2D* character) {
    m_characters.insert(character);
}


inline void PlatformComponent::Unregister(Controller2D* character) {
    m_characters.erase(character);
}

inline void PlatformComponent::UnregisterAll() {
    m_characters.clear();
}


