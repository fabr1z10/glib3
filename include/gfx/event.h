//
//  event.h
//  glib
//
//  Created by Fabrizio Venturini on 13/06/2018.
//
//

#ifndef event_h
#define event_h

#include <gfx/ref.h>
#include <functional>
#include <unordered_map>

// generic class that enables to register interest
// objects can expose different events other objects can register to
// an event require a function (callback) to call when something happens
// this func can be a global function or a member function
// in this case every object registering must be a ref, in order that we
// can detect when it goes out of scope

template<typename Args>
class Event {
private:
    struct Callback {
        std::function<void(Args)> callback;
    };
public:
    Event() : m_enabled(true) {}
    void setEnabled(bool value) {
        m_enabled = value;
    }

    // register interest in this event with context
    void Register(Ref* object, std::function<void(Args)> f) {
        m_callbacks[object->GetId()] = Callback{ f };
    }
    
    void Unregister(Ref* obj) {
        m_callbacks.erase(obj->GetId());
    }

    void Fire(Args args) {
        if (!m_enabled)
            return;

        for (auto it = m_callbacks.begin(); it != m_callbacks.end(); /* no inc */)
        {
            if (!Ref::isAlive(it->first)) {
                // observer is no longer alive, remove the callback
                m_callbacks.erase(it++);
            }
            else {
                it->second.callback (args);
                it++;
            }
        }
    }
    
private:
    bool m_enabled;
    std::unordered_map<int, Callback> m_callbacks;
};

#endif /* event_h */
